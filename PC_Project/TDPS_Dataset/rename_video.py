import os
from string import ascii_lowercase

videoPath = '/home/psc/Desktop/Carset/Video'
os.chdir(videoPath)
videos = os.listdir(videoPath)
videoNum = len(videos)
print(videos)
for i in range(videoNum):
    os.rename(videos[i], ascii_lowercase[i] + '.mov')