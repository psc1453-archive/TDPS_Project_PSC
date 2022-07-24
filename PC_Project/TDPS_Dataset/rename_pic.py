import os
from string import ascii_lowercase
import random
from concurrent.futures import ThreadPoolExecutor

# picturePath = '/home/psc/Desktop/Carset/FullFrame/1080p'
picturePath = '/run/media/psc/LinuxData/Carset/FullFrame/1080p'
os.chdir(picturePath)
pictures = os.listdir(picturePath)
pictureNum = len(pictures)
orderedNum = [i for i in range(pictureNum)]
randomNum = orderedNum.copy()
random.shuffle(randomNum)
# for i in randomNum:
#     os.rename(pictures[i], "{:0>7d}".format(i) + '.jpg')

def renamePic(num):
    os.rename(pictures[num], "{:0>7d}".format(randomNum[num]) + '.jpg')
    print(num)

with ThreadPoolExecutor(max_workers=24) as pool:
    pool.map(renamePic, orderedNum)
