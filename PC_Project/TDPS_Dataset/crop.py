import cv2
import os
from concurrent.futures import ThreadPoolExecutor

def crop_img(resolution):
    aim_resolution = resolution

    files_num_f = len(os.listdir(os.path.dirname('/home/psc/Desktop/carset/Full_Frame/1080p/f/')))
    files_num_l = len(os.listdir(os.path.dirname('/home/psc/Desktop/carset/Full_Frame/1080p/l/')))
    files_num_r = len(os.listdir(os.path.dirname('/home/psc/Desktop/carset/Full_Frame/1080p/r/')))

    files_list_f = [i + 1 for i in range(files_num_f)]
    files_list_l = [i + 1 for i in range(files_num_l)]
    files_list_r = [i + 1 for i in range(files_num_r)]

    resolution_dir = '/home/psc/Desktop/carset/Cropped/' + aim_resolution

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

    def crop_image(addr_in, addr_out, num):
        num_str = "{:0>6d}".format(num)
        read_address = addr_in + num_str + '.jpg'
        write_address = addr_out + num_str + '.jpg'
        img = cv2.imread(read_address)
        # get_resolution = lambda shape: (shape[1], shape[0])
        # img_resolution = get_resolution(img.shape)
        img_shape = img.shape[0:2]
        img_width = img_shape[1]
        y_crop_start = round(img_shape[0] * 0.4)
        y_crop_end = round(img_shape[0] * 0.6)

        cropped = img[y_crop_start: y_crop_end, 0: img_width]
        cv2.imwrite(write_address, cropped)
        print(addr_out + " finish " + str(num))

    call_crop_args_f = [['/home/psc/Desktop/carset/Full_Frame/' + aim_resolution + '/f/'] * files_num_f,
                        ['/home/psc/Desktop/carset/Cropped/' + aim_resolution + '/f/'] * files_num_f, files_list_f]
    call_crop_args_l = [['/home/psc/Desktop/carset/Full_Frame/' + aim_resolution + '/l/'] * files_num_l,
                        ['/home/psc/Desktop/carset/Cropped/' + aim_resolution + '/l/'] * files_num_l, files_list_l]
    call_crop_args_r = [['/home/psc/Desktop/carset/Full_Frame/' + aim_resolution + '/r/'] * files_num_r,
                        ['/home/psc/Desktop/carset/Cropped/' + aim_resolution + '/r/'] * files_num_r, files_list_r]

    with ThreadPoolExecutor(max_workers=24) as pool:
        pool.map(crop_image, *call_crop_args_f)
        pool.map(crop_image, *call_crop_args_l)
        pool.map(crop_image, *call_crop_args_r)


resolution_list = ['180p', '135p', '100p', '90p', '54p', '45p']

for res in resolution_list:
    crop_img(res)