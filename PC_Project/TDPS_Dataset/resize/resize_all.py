import cv2
import os
from concurrent.futures import ThreadPoolExecutor

aim_resolution = '120p'
aim_resolution_value = (213, 120)

files_num_f = len(os.listdir(os.path.dirname('/home/psc/Desktop/carset/Full_Frame/1080p/f/')))
files_num_l = len(os.listdir(os.path.dirname('/home/psc/Desktop/carset/Full_Frame/1080p/l/')))
files_num_r = len(os.listdir(os.path.dirname('/home/psc/Desktop/carset/Full_Frame/1080p/r/')))

files_list_f = [i + 1 for i in range(files_num_f)]
files_list_l = [i + 1 for i in range(files_num_l)]
files_list_r = [i + 1 for i in range(files_num_r)]

resolution_dir = '/home/psc/Desktop/carset/Full_Frame/' + aim_resolution

if not os.path.exists(resolution_dir):
    os.makedirs(resolution_dir)
    os.makedirs(resolution_dir + '/f')
    os.makedirs(resolution_dir + '/l')
    os.makedirs(resolution_dir + '/r')
else:
    if not os.path.exists(resolution_dir + '/f'):
        os.makedirs(resolution_dir + '/f')
    if not os.path.exists(resolution_dir + '/l'):
        os.makedirs(resolution_dir + '/l')
    if not os.path.exists(resolution_dir + '/r'):
        os.makedirs(resolution_dir + '/r')


def resize_image(addr_in, addr_out, num):
    num_str = "{:0>6d}".format(num)
    read_address = addr_in + num_str + '.jpg'
    write_address = addr_out + num_str + '.jpg'
    pic = cv2.imread(read_address)
    pic = cv2.resize(pic, aim_resolution_value, interpolation=cv2.INTER_CUBIC)
    cv2.imwrite(write_address, pic)
    print(addr_out + " finish " + str(num))


def action(num1, num2):
    print(str(num1) + ' ' + str(num2))


call_resize_args_f = [['/home/psc/Desktop/carset/Full_Frame/1080p/f/'] * files_num_f,
                      ['/home/psc/Desktop/carset/Full_Frame/' + aim_resolution + '/f/'] * files_num_f, files_list_f]
call_resize_args_l = [['/home/psc/Desktop/carset/Full_Frame/1080p/l/'] * files_num_l,
                      ['/home/psc/Desktop/carset/Full_Frame/' + aim_resolution + '/l/'] * files_num_l, files_list_l]
call_resize_args_r = [['/home/psc/Desktop/carset/Full_Frame/1080p/r/'] * files_num_r,
                      ['/home/psc/Desktop/carset/Full_Frame/' + aim_resolution + '/r/'] * files_num_r, files_list_r]

# with ThreadPoolExecutor(max_workers=24) as pool:
#     pool.map(resize_image, *call_resize_args_f)
#     pool.map(resize_image, *call_resize_args_l)
#     pool.map(resize_image, *call_resize_args_r)

print(call_resize_args_r)