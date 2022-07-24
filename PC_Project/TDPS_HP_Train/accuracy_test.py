import torch as tc
from matplotlib import pyplot as plt
from torch.utils.data import DataLoader
from torchvision import transforms

from TDPS_CNN_54p import TDPS_CNN_54p
from TDPS_HP_DataSet import TDPS_HP_DataSet

import torch.nn.functional as F

def quant(tensor_in, bits, min, max):
    res = (max - min) / 2 ** bits
    tensor = tensor_in.clamp(min, max - res)
    steps = ((tensor - min) / res).int()
    # print(steps)
    tensor_out = steps * res + min
    return tensor_out

batch_size = 32
resolution = '54p'

# Image processing: PIL -> Tensor, Normalization
data_tf = transforms.Compose \
    ([transforms.ToTensor(),
      transforms.Normalize([0.5], [0.5])])

test_dataset = TDPS_HP_DataSet(root='/run/media/psc/LinuxData/Carset/Classified/Cropped', resolution=resolution,
                               train=True, transform=data_tf)

test_loader = DataLoader(test_dataset, batch_size=batch_size, shuffle=True, num_workers=22)


if tc.cuda.is_available():
    coef = tc.Tensor([0, 1, 2, 3, 4, 5, 6]).cuda()
    model = TDPS_CNN_54p().cuda().half()
    model.load_state_dict(tc.load('net54/wetnet0.00303766131401062.pth', map_location='cuda'))
else:
    coef = tc.Tensor([0, 1, 2, 3, 4, 5, 6])
    model = TDPS_CNN_54p()
    model.load_state_dict(tc.load('net54/wetnet0.00303766131401062.pth', map_location='cpu'))


model.eval()
# print(model.layer_1[0].weight.data)
# model.layer_1[0].weight.data = model.layer_1[0].weight.data * 2
# if tc.cuda.is_available():
#     model.layer_1[0].weight.data = quant(model.layer_1[0].weight.data, 6, -1, 1).half()
# else:
#     model.layer_1[0].weight.data = quant(model.layer_1[0].weight.data, 6, -1, 1)
# model.layer_2[0].weight.data = model.layer_2[0].weight.data * 2
# if tc.cuda.is_available():
#     model.layer_2[0].weight.data = quant(model.layer_2[0].weight.data, 6, -1, 1).half()
# else:
#     model.layer_2[0].weight.data = quant(model.layer_2[0].weight.data, 6, -1, 1)
# print(model.layer_2[0].weight.data*3)
cnt = 0
for batch_idx, (img, lab) in enumerate(test_loader):

    current_size = lab.size(0)
    if tc.cuda.is_available():
        # Reshape
        x = img.cuda().half()
        # Reshape y
        y = lab.reshape(current_size).cuda()
    else:
        # Reshape
        x = img
        # Reshape y
        y = lab.reshape(current_size)
    # Compute
    out = F.softmax(model(x), 1).mul(coef)
    # print(out)
    # print(out)
    out = out.sum(1)
    print(out)
    out_list = [i.item() for i in out]
    label_list = [i.item() for i in lab]
    for i in range(len(out_list)):
        if abs(out_list[i] - label_list[i]) > 1:
            cnt = cnt + 1
        # print(('fuck!!!!!!   ' if abs(out_list[i] - label_list[i]) > 1 else '') + str(out_list[i] - label_list[i]) + ' ' + str(label_list[i]) + ' ' + str(out_list[i]))
        pass
print(cnt)


