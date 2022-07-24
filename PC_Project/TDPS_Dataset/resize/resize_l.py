import cv2
import threading
import os

files_num = len(os.listdir(os.path.dirname('/home/psc/Desktop/carset/1080p/l/')))

files_list = [i + 1 for i in range(files_num)]


def resize_image(addr_in, addr_out):
    while len(files_list) != 0:
        num = files_list[0]
        del files_list[0]
        num_str = "{:0>6d}".format(num)
        read_address = addr_in + num_str + '.jpg'
        write_address = addr_out + num_str + '.jpg'
        pic = cv2.imread(read_address)
        pic = cv2.resize(pic, (160, 90), interpolation=cv2.INTER_CUBIC)
        cv2.imwrite(write_address, pic)
        print("finish " + str(num))


for i in range(23):
    thread1 = threading.Thread(target=resize_image,
                               args=['/home/psc/Desktop/carset/1080p/l/', '/home/psc/Desktop/carset/90p/l/'])
    thread1.start()
