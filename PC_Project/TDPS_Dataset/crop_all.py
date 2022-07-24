import cv2
import os
from concurrent.futures import ThreadPoolExecutor

files_num = len(os.listdir(os.path.dirname('/run/media/psc/LinuxData/Carset/FullFrame/1080p/')))


def crop_img(resolution):
    aim_resolution = resolution

    files_list = [i + 1 for i in range(files_num)]

    resolution_dir = '/run/media/psc/LinuxData/Carset/Cropped/' + aim_resolution

    if not os.path.exists(resolution_dir):
        os.makedirs(resolution_dir)

    def crop_image(addr_in, addr_out, num):
        num_str = "{:0>7d}".format(num)
        read_address = addr_in + num_str + '.jpg'
        write_address = addr_out + num_str + '.jpg'
        img = cv2.imread(read_address)
        # get_resolution = lambda shape: (shape[1], shape[0])
        # img_resolution = get_resolution(img.shape)
        img_shape = img.shape[0:2]
        img_height = img_shape[0]
        y_crop_start = round(img_shape[0] * 0.4)
        y_crop_end = round(img_shape[0] * 0.6)
        cropped = img[0: img_height, 12: 84]
        cv2.imwrite(write_address, cropped)
        print(addr_out + " finish " + str(num))

    call_crop_args = [['/run/media/psc/LinuxData/Carset/FullFrame/' + aim_resolution + '/'] * files_num,
                      ['/run/media/psc/LinuxData/Carset/Cropped/' + aim_resolution + '/'] * files_num, files_list]

    with ThreadPoolExecutor(max_workers=24) as pool:
        pool.map(crop_image, *call_crop_args)

# resolution_list = ['180p', '135p', '100p', '90p', '54p', '45p']
# resolution_list = ['1080p', '540p', '360p', '180p', '90p', '45p']
resolution_list = ['54p']
for res in resolution_list:
    crop_img(res)
