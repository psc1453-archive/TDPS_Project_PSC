import cv2
import os
from concurrent.futures import ThreadPoolExecutor

aim_resolution = '72p'
aim_resolution_value = (96, 72)

files_num = len(os.listdir(os.path.dirname('/run/media/psc/LinuxData/Carset/FullFrame/1080p/')))
files_list = [i + 1 for i in range(files_num)]

resolution_dir = '/run/media/psc/LinuxData/Carset/Cropped/' + aim_resolution

if not os.path.exists(resolution_dir):
    os.makedirs(resolution_dir)



def resize_image(addr_in, addr_out, num):
    num_str = "{:0>7d}".format(num)
    read_address = addr_in + num_str + '.jpg'
    write_address = addr_out + num_str + '.jpg'
    pic = cv2.imread(read_address)
    pic = cv2.resize(pic, aim_resolution_value, interpolation=cv2.INTER_CUBIC)
    cv2.imwrite(write_address, pic)
    print(addr_out + " finish " + str(num))


def action(num1, num2):
    print(str(num1) + ' ' + str(num2))


call_resize_args = [['/run/media/psc/LinuxData/Carset/Cropped/120p/'] * files_num,
                      ['/run/media/psc/LinuxData/Carset/Cropped/' + aim_resolution + '/'] * files_num, files_list]

with ThreadPoolExecutor(max_workers=24) as pool:
    pool.map(resize_image, *call_resize_args)
