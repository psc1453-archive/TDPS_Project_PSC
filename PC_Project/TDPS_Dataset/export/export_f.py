# 导入所需要的库
import cv2
import numpy as np


# 定义保存图片函数
# image:要保存的图片名字
# addr；图片地址与相片名字的前部分
# num: 相片，名字的后缀。int 类型
def save_image(image, addr, num):
    address = addr + "{:0>6d}".format(num) + '.jpg'
    cv2.imwrite(address, image)


# 读取视频文件
videoCapture = cv2.VideoCapture("/home/psc/Desktop/carset/f3.MOV")
# 通过摄像头的方式
# videoCapture=cv2.VideoCapture(1)

# 读帧
success = True
i = 9677
while success:
    i = i + 1
    success, frame = videoCapture.read()
    save_image(frame, '/home/psc/Desktop/carset/f/', i)
    if success:
        print('save image:', i)