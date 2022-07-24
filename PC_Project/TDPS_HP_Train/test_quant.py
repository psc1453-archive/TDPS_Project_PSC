import torch

def quant_tensor(num_in, q, min, max):
    step = (max - min) / (2 ** q)
    tensorToQuant = torch.clamp(num_in, min, max - step)
    levels = torch.round((tensorToQuant - min) / step)
    out = levels * step + min
    return out


import torch as tc
from matplotlib import pyplot as plt
from torch.utils.data import DataLoader
from torchvision import transforms

from TDPS_CNN_90p import TDPS_CNN_90p
from TDPS_HP_DataSet import TDPS_HP_DataSet

batch_size = 64
learning_rate = 5 * 1e-3
num_epochs = 200
resolution = '90p'

# Image processing: PIL -> Tensor, Normalization
data_tf = transforms.Compose \
    ([transforms.ToTensor(),
      transforms.Normalize([0.5], [0.5])])

# Import Mnist dataset
train_dataset = TDPS_HP_DataSet(root='/run/media/psc/LinuxData/Carset/Classified/FullFrame', resolution=resolution,
                                train=True, transform=data_tf)
test_dataset = TDPS_HP_DataSet(root='/run/media/psc/LinuxData/Carset/Classified/FullFrame', resolution=resolution,
                               train=True, transform=data_tf)

# Creat iter: Dataloader
train_loader = DataLoader(train_dataset, batch_size=batch_size, shuffle=True, num_workers=22)
test_loader = DataLoader(test_dataset, batch_size=batch_size, shuffle=True, num_workers=22)

if torch.cuda.is_available():
    model = TDPS_CNN_90p().cuda().half()
    model.load_state_dict(torch.load('nets/net0.35033679008483887.pth', map_location='cuda'))
else:
    model = TDPS_CNN_90p()
    model.load_state_dict(torch.load('nets/net0.35033679008483887.pth', map_location='cpu'))

model.layer_1[0].weight.data = quant_tensor(model.layer_1[0].weight.data, 8, -1, 1)
model.layer_1[0].bias.data = quant_tensor(model.layer_1[0].bias.data, 8, -1, 1)

model.layer_2[0].weight.data = quant_tensor(model.layer_2[0].weight.data, 8, -1, 1)
model.layer_2[0].bias.data = quant_tensor(model.layer_2[0].bias.data, 8, -1, 1)

model.layer_3[0].weight.data = quant_tensor(model.layer_3[0].weight.data, 8, -1, 1)
model.layer_3[0].bias.data = quant_tensor(model.layer_3[0].bias.data, 8, -1, 1)

model.fc[0].weight.data = quant_tensor(model.fc[0].weight.data, 8, -1, 1)
model.fc[0].bias.data = quant_tensor(model.fc[0].bias.data, 8, -1, 1)

model.fc[2].weight.data = quant_tensor(model.fc[2].weight.data, 8, -1, 1)
model.fc[2].bias.data = quant_tensor(model.fc[2].bias.data, 8, -1, 1)

for times in range(100):

    # model.load_state_dict(tc.load('45p1.pth'))
    # Using CrossEntropyLoss
    criterion = tc.nn.CrossEntropyLoss()
    optimizer = tc.optim.SGD(model.parameters(), lr=learning_rate, momentum=0.8)
    # optimizer = tc.optim.Adagrad(model.parameters(), lr=learning_rate)

    # For test data, count epoch
    times = []
    # For test data, accuracy achievement
    achieve = []

    loss_list = []

    coef = tc.Tensor([0, 1, 2, 3, 4, 5, 6]).cuda()

    # Begin training and testing
    for epoch in range(num_epochs):
        # Train mode

        # Test mod
        model.eval()
        # Right prediction count
        right = 0
        # Total input count
        total = 0
        # Accuracy list for each test
        accuracy_list = []

        # Test

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
            out = model(x).mul(coef).sum(1)
            # print('f: ')
            # print(out)
            # print('y: ')
            # print(y)
            # print('out: ')
            # print(model(x).data.max(1, keepdim=True)[1].squeeze(1))
            # print(y)
            # print(out)
            # Pick up actual predict number
            # pred = out.data.max(1, keepdim=True)[1].squeeze(1)
            # print(pred.size())
            # pred = out.mul(coef).sum(1)
            # Compare labels and predictions
            # comparison = y.eq(pred)
            diff = (y - out).abs().sum().item() / batch_size
            # Count accurate predictions and compute accuracy
            # accuracy = comparison.sum().float().item() / float(current_size)
            # Append accuracy value to list for finding max
            # accuracy_list.append(accuracy)
            accuracy_list.append(diff)
            if batch_idx == 40:
                break

        # Find max
        max_accuracy = max(accuracy_list)
        # Append time
        times.append(epoch)
        # Append achievement
        achieve.append(max_accuracy)
        # Plot
        plt.plot(times, achieve)
        plt.plot(times, loss_list)
        plt.show()
        print("epoch: " + str(epoch) + ', loss: ' + str(printable_loss) + ', accuracy: ' + str(max_accuracy))

        '''
        # Self input test

        image = Image.open('./5.jpg')
        tran = data_tf = transforms.Compose\
            ([transforms.ToTensor(),
                transforms.Normalize([0.5], [0.5])])
        image = tran(image).reshape(1, 1, 28, 28)
        if tc.cuda.is_available():
            image = tc.autograd.Variable(image).cuda()
        else:
            image = tc.autograd.Variable(image)
        out = model(image)
        pred = out.data.max(1, keepdim=True)[1].squeeze(1).item()
        print(pred)
        '''
    plt.plot(times, achieve)
    plt.plot(times, loss_list)
    plt.savefig('./nets/net' + str(max_accuracy) + '.jpg')
    plt.show()
    tc.save(model.state_dict(), './nets/net' + str(max_accuracy) + '.pth')

