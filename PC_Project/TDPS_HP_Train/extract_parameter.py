import torch
from TDPS_CNN_90p import TDPS_CNN_90p
import numpy as np
import scipy.io

net = TDPS_CNN_90p()
net.load_state_dict(torch.load('nets/net0.35033679008483887.pth', map_location='cpu'))

conv1_weight = net.layer_1[0].weight.data
conv1_bias = net.layer_1[0].bias.data

conv2_weight = net.layer_2[0].weight.data
conv2_bias = net.layer_2[0].bias.data

conv3_weight = net.layer_3[0].weight.data
conv3_bias = net.layer_3[0].bias.data

fc1_weight = net.fc[0].weight.data
fc1_bias = net.fc[0].bias.data

fc2_weight = net.fc[2].weight.data
fc2_bias = net.fc[2].bias.data

net_parameters = {
    'conv1_weight': np.array(conv1_weight.numpy()),\
    'conv1_bias':   np.array(conv1_bias.numpy()),\
    'conv2_weight': np.array(conv2_weight.numpy()),\
    'conv2_bias':   np.array(conv2_bias.numpy()),\
    'conv3_weight': np.array(conv3_weight.numpy()),\
    'conv3_bias':   np.array(conv3_bias.numpy()),\
    'fc1_weight': np.array(fc1_weight.numpy()),\
    'fc1_bias':   np.array(fc1_bias.numpy()),\
    'fc2_weight': np.array(fc2_weight.numpy()),\
    'fc2_bias':   np.array(fc2_bias.numpy())
}

scipy.io.savemat('nn_parameters.mat', net_parameters)