# 导入所需要的库
import cv2
import numpy as np
from concurrent.futures import ThreadPoolExecutor
import os


# 定义保存图片函数
# image:要保存的图片名字
# addr；图片地址与相片名字的前部分
# num: 相片，名字的后缀。int 类型
def save_image(image, addr, videoName, num):
    address = addr + videoName + "{:0>6d}".format(num) + '.jpg'
    pic = cv2.resize(image, (1920, 1080), interpolation=cv2.INTER_CUBIC)
    cv2.imwrite(address, pic)


def cut_video(fileName):
    # 读取视频文件
    videoCapture = cv2.VideoCapture('/home/psc/Desktop/Carset/Video/' + fileName + '.mov')
    # 通过摄像头的方式
    # videoCapture=cv2.VideoCapture(1)

    # 读帧
    success = True
    i = 0
    while success:
        i = i + 1
        success, frame = videoCapture.read()
        save_image(frame, '/home/psc/Desktop/Carset/FullFrame/1080p/', fileName, i)
        if success:
            print('save image: ' + fileName + ' ' + str(i))

videoPath = '/home/psc/Desktop/Carset/Video'
videos = os.listdir(videoPath)
videoNames = [fileName[0] for fileName in videos]
# print(videoNames)
# print(videos)
with ThreadPoolExecutor(max_workers=24) as pool:
    pool.map(cut_video, videoNames)