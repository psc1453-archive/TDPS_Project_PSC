# 导入所需要的库
import cv2
import numpy as np
from concurrent.futures import ThreadPoolExecutor
import os

videoPath = '/run/media/psc/LinuxData/wet/'
picPath = '/run/media/psc/LinuxData/wetset/'
# 定义保存图片函数
# image:要保存的图片名字
# addr；图片地址与相片名字的前部分
# num: 相片，名字的后缀。int 类型
def save_image(image, addr, videoName, num):
    address = addr + videoName[0:3] + "{:0>6d}".format(num) + '.jpg'
    pic = cv2.resize(image, (96, 54), interpolation=cv2.INTER_CUBIC)
    cropped = pic[0: 54, 12: 84]
    cv2.imwrite(address, cropped)


def cut_video(fileName):
    if os.path.exists(picPath+fileName[0:3]):
        pass;
    else:
        os.mkdir(picPath+fileName[0:3])
    # 读取视频文件
    videoCapture = cv2.VideoCapture(videoPath + fileName)
    # 通过摄像头的方式
    # videoCapture=cv2.VideoCapture(1)

    # 读帧
    success = True
    i = 0
    while success:
        i = i + 1
        success, frame = videoCapture.read()
        save_image(frame, picPath+fileName[0:3] + '/', fileName, i)
        if success:
            print('save image: ' + fileName + ' ' + str(i))


videos = os.listdir(videoPath)
print(videos)
with ThreadPoolExecutor(max_workers=24) as pool:
    pool.map(cut_video, videos)