from torch import nn


class TDPS_CNN_54p(nn.Module):
    def __init__(self):
        super(TDPS_CNN_54p, self).__init__()
        self.layer_1 = nn.Sequential\
            (
                nn.Conv2d(1, 4, kernel_size=3),
                nn.BatchNorm2d(4),
                nn.ReLU(inplace=True),
                # nn.MaxPool2d(kernel_size=2, stride=2, ceil_mode=True)
            )

        self.layer_2 = nn.Sequential\
            (
                nn.Conv2d(4, 4, kernel_size=3),
                nn.BatchNorm2d(4),
                nn.ReLU(inplace=True),
                nn.MaxPool2d(kernel_size=2, stride=2)
            )

        self.layer_3 = nn.Sequential\
            (
                nn.Conv2d(4, 8, kernel_size=3),
                nn.BatchNorm2d(8),
                nn.ReLU(inplace=True),
                nn.MaxPool2d(kernel_size=2, stride=2, ceil_mode=True)
            )

        self.fc = nn.Sequential\
            (
                nn.Linear(16*12*8, 200),
                nn.Dropout(inplace=True),
                nn.ReLU(inplace=True),
                # nn.Linear(250, 128),
                # nn.ReLU(inplace=True),
                nn.Linear(200, 7),
                # nn.Dropout(inplace=True),
                # nn.Softmax(1)
            )

    def forward(self, x):
        x = self.layer_1(x)
        x = self.layer_2(x)
        x = self.layer_3(x)
        x = x.reshape(x.size(0), -1)
        x = self.fc(x)
        return x