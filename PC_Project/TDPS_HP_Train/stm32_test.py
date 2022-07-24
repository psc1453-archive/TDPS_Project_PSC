from PIL import Image
import numpy as np
import torch
from torchvision import transforms
from TDPS_CNN_54p import *
import pyperclip
import torch.nn.functional as F

coef = torch.Tensor([0, 1, 2, 3, 4, 5, 6]).cuda()

if torch.cuda.is_available():
    model = TDPS_CNN_54p().cuda()
else:
    model = TDPS_CNN_54p()

model.load_state_dict(torch.load('net54/net0.004316696897149086.pth'))

img = Image.open('images/nnimg/0000468.jpg')
img = img.resize((72, 54), Image.ANTIALIAS)
img = img.convert("L")
# img.show()

tran = transforms.Compose\
    ([transforms.ToTensor(),
        transforms.Normalize([0.5], [0.5])])
image = tran(img).reshape(1, 1, 54, 72).cuda()

pixel_str = ''
for row in range(54):
    for col in range(72):
        pixel = float(image[0][0][row][col])
        pixel_str = pixel_str + str(pixel) + ','
pyperclip.copy(pixel_str)
with open('image.txt', 'w+') as f:
    f.write(pixel_str)

model.eval()
out = model(image)
out = F.softmax(out, 1)
for i in range(7):
    print(out[0][i])
out = out.mul(coef)
out = out.sum(1)

print(out)

