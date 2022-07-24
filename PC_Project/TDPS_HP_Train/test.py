# from PIL import Image
# import numpy as np
# import torch
# from torchvision import transforms
# from TDPS_CNN_54p import *
#
# coef = torch.Tensor([0, 1, 2, 3, 4, 5, 6])
#
# model = TDPS_CNN_54p()
#
# model.load_state_dict(torch.load('nets/net0.4403424561023712_no_bias.pth', map_location='cuda'))
#
# img = Image.open('images/nnimg/t.jpg')
# img = img.resize((96, 54), Image.ANTIALIAS)
# img = img.convert("L")
#
# tran = transforms.Compose\
#     ([transforms.ToTensor(),
#         transforms.Normalize([0.5], [0.5])])
# image = tran(img).reshape(1, 1, 54, 96)
#
# print(image)
#
# out = model(image).mul(coef)
# print(out)
# out = out.sum(1)
#
# print(out)

import torch
import torch.nn.functional as F

t = torch.Tensor([[1,2,3]])
print(F.softmax(t, 1))

