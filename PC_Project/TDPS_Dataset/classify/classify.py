import os
import shutil

resolution = '54p'
imgShape = 'Cropped'

classifiedDir = '/run/media/psc/LinuxData/Carset/Classified/' + imgShape + '/'
resolution_dir = classifiedDir + resolution
sourceDir = '/run/media/psc/LinuxData/Carset/' + imgShape + '/' + resolution

if not os.path.exists(resolution_dir):
    os.makedirs(resolution_dir)
    os.makedirs(resolution_dir + '/0')
    os.makedirs(resolution_dir + '/1')
    os.makedirs(resolution_dir + '/2')
    os.makedirs(resolution_dir + '/6')
    os.makedirs(resolution_dir + '/5')
    os.makedirs(resolution_dir + '/4')
    os.makedirs(resolution_dir + '/3')
else:
    if not os.path.exists(resolution_dir + '/0'):
        os.makedirs(resolution_dir + '/0')
    if not os.path.exists(resolution_dir + '/1'):
        os.makedirs(resolution_dir + '/1')
    if not os.path.exists(resolution_dir + '/2'):
        os.makedirs(resolution_dir + '/2')
    if not os.path.exists(resolution_dir + '/6'):
        os.makedirs(resolution_dir + '/6')
    if not os.path.exists(resolution_dir + '/5'):
        os.makedirs(resolution_dir + '/5')
    if not os.path.exists(resolution_dir + '/4'):
        os.makedirs(resolution_dir + '/4')
    if not os.path.exists(resolution_dir + '/3'):
        os.makedirs(resolution_dir + '/3')

os.system('cat Dataset.csv | egrep \'psc|wyx|wyh|yyx|zxc|lyx\' > LabeledDataset.txt')

L11 = []
L10 = []
L01 = []
C00 = []
R01 = []
R10 = []
R11 = []
FUK = []

with open('LabeledDataset.txt', 'r') as dataset:
    labeledDataset = dataset.readlines()
    for labeledPicture in labeledDataset:
        idx, fileName, label, user = labeledPicture.split(',')
        if label == 'L11':
            L11.append(fileName)
        elif label == 'L10':
            L10.append(fileName)
        elif label == 'L01':
            L01.append(fileName)
        elif label == '00':
            C00.append(fileName)
        elif label == 'R01':
            R01.append(fileName)
        elif label == 'R10':
            R10.append(fileName)
        elif label == 'R11':
            R11.append(fileName)
        else:
            FUK.append(fileName)

L11_existed = os.listdir(resolution_dir + '/0')
L10_existed = os.listdir(resolution_dir + '/1')
L01_existed = os.listdir(resolution_dir + '/2')
C00_existed = os.listdir(resolution_dir + '/3')
R01_existed = os.listdir(resolution_dir + '/4')
R10_existed = os.listdir(resolution_dir + '/5')
R11_existed = os.listdir(resolution_dir + '/6')

for img in L11:
    if img in L11_existed:
        pass
    else:
        shutil.copyfile(sourceDir + '/' + img, resolution_dir + '/0/' + img)
for img in L10:
    if img in L10_existed:
        pass
    else:
        shutil.copyfile(sourceDir + '/' + img, resolution_dir + '/1/' + img)
for img in L01:
    if img in L01_existed:
        pass
    else:
        shutil.copyfile(sourceDir + '/' + img, resolution_dir + '/2/' + img)
for img in C00:
    if img in C00_existed:
        pass
    else:
        shutil.copyfile(sourceDir + '/' + img, resolution_dir + '/3/' + img)
for img in R11:
    if img in R11_existed:
        pass
    else:
        shutil.copyfile(sourceDir + '/' + img, resolution_dir + '/6/' + img)
for img in R10:
    if img in R10_existed:
        pass
    else:
        shutil.copyfile(sourceDir + '/' + img, resolution_dir + '/5/' + img)
for img in R01:
    if img in R01_existed:
        pass
    else:
        shutil.copyfile(sourceDir + '/' + img, resolution_dir + '/4/' + img)