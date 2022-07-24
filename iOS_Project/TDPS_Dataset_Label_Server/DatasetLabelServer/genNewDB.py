from PandasOperation import *


def genNewDB(dbPath, datasetPath):
    db = pandas_read_csv(dbPath)
    for path in os.listdir(datasetPath):
        db = pandas_append_new_row(db, path, '', '')
        print(path + ' added')

    pandas_save_csv(db, dbPath)

dbPath = './Dataset.csv'
pandas_create_csv(dbPath)

datasetPath = '/mnt/NAS/share/Nginx/html/html/dataset/180p'
genNewDB(dbPath, datasetPath)