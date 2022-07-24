import torch as tc
from torch.utils.data import Dataset, DataLoader
import os
from PIL import Image


class TDPS_HP_DataSet(Dataset):
    def __init__(self, root, resolution, train, transform):
        self.path = os.path.join(root, resolution)
        self.resolution = resolution
        self.train = train
        self.transform = transform

        class_idx = -1
        instances = []
        for root, _, files in sorted(os.walk(self.path)):
            for file in sorted(files):
                path = os.path.join(root, file)
                item = path, class_idx
                instances.append(item)
            class_idx += 1
        self.instances = instances

    def __getitem__(self, index):
        file_path, label = self.instances[index]
        img = Image.open(file_path)
        img = img.convert('L')
        if self.transform is not None:
            img = self.transform(img)
        return img, label

    def __len__(self):
        return len(self.instances)
