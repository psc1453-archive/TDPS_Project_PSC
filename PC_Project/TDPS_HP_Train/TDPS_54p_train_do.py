import torch as tc
from matplotlib import pyplot as plt
from torch.utils.data import DataLoader
from torchvision import transforms

from TDPS_CNN_54p_do import TDPS_CNN_54p
from TDPS_HP_DataSet import TDPS_HP_DataSet

import torch.nn.functional as F

train_batch_size = 8
test_batch_size = 128
learning_rate = 1 * 1e-3
num_epochs = 5
resolution = '54p'


# Image processing: PIL -> Tensor, Normalization
train_tf = transforms.Compose \
    ([transforms.ColorJitter(brightness=0.6, contrast=0.6, saturation=1),
      transforms.ToTensor(),
      transforms.Normalize([0.5], [0.5])])

test_tf = transforms.Compose \
    ([transforms.ToTensor(),
      transforms.Normalize([0.5], [0.5])])

# Import Mnist dataset
train_dataset = TDPS_HP_DataSet(root='/run/media/psc/LinuxData/Carset/Classified/Cropped/split/54p/train', resolution=resolution,
                                train=True, transform=train_tf)
test_dataset = TDPS_HP_DataSet(root='/run/media/psc/LinuxData/Carset/Classified/Cropped/split/54p/test', resolution=resolution,
                               train=True, transform=test_tf)

# Creat iter: Dataloader
train_loader = DataLoader(train_dataset, batch_size=train_batch_size, shuffle=True, num_workers=22)
test_loader = DataLoader(test_dataset, batch_size=test_batch_size, shuffle=True, num_workers=22)

for times in range(100):
    # Create instance of nn
    if tc.cuda.is_available():
        model = TDPS_CNN_54p().cuda().half()
        # tc.save(model.state_dict(), 'net54/initial.pth')
        model.load_state_dict(tc.load('final_net/a0.10675850510597229.pth', map_location='cuda'))
    else:
        model = TDPS_CNN_54p()
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
        model.train()
        # Unzip train_loader
        for batch_idx, (img, lab) in enumerate(train_loader):
            current_size = lab.size(0)
            if tc.cuda.is_available():
                # Reshape images (64 x 1 x 28 x 28) -> (64, 28 * 28)
                x = tc.autograd.Variable(img).cuda().half()
                # Reshape target label y (64 x 1) -> (64)
                y = tc.autograd.Variable(lab.reshape(current_size)).cuda()
            else:
                # Reshape images (64 x 1 x 28 x 28) -> (64, 28 * 28)
                x = tc.autograd.Variable(img)
                # Reshape target label y (64 x 1) -> (64)
                y = tc.autograd.Variable(lab.reshape(current_size))

            # Compute output
            out = model(x)
            # print(out)
            # Compute loss
            loss = criterion(out, y)
            # Convert to printable loss
            printable_loss = loss.data.item()

            # Zerofill grad
            optimizer.zero_grad()
            # Back propagation
            loss.backward()
            # Update grad
            optimizer.step()

        loss_list.append(printable_loss)
        # Test mod
        model.eval()
        # Right prediction count
        right = 0
        # Total input count
        total = 0
        # Accuracy list for each test
        accuracy_list = []

        # Test
        model.eval()
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
            out = F.softmax(model(x), 1).mul(coef).sum(1)
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
            diff = (y - out).abs().sum().item() / test_batch_size
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
    plt.savefig('./final_net/a' + str(max_accuracy) + '.jpg')
    plt.show()
    tc.save(model.state_dict(), './final_net/a' + str(max_accuracy) + '.pth')
