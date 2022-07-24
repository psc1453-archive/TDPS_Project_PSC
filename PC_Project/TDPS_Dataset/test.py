import shutil
import os

lst = os.listdir('test/src')
shutil.copyfile('test/src/1.txt', 'test/tgt/3.txt')
