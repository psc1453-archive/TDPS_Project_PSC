import pandas as pd
import csv
import os



def pandas_create_csv(path):
    d = {'fileName': [], 'label': [], 'user': []}
    df = pd.DataFrame(d)
    df.to_csv(path)
    return pandas_read_csv(path)


def pandas_read_csv(path):
    db = pd.read_csv(path, index_col=0)
    return db

def pandas_save_csv(db, path):
    db.to_csv(path, index=True)

def genFileName(db):
    if pandas_nonlabeled_exist(db):
        return pandas_find_next_nonlabeled_fileName(db)
    else:
        return '0.png'

def pandas_remove_row(db, row):
    df = db.drop(row)
    df = df.reset_index().drop('index', axis=1)
    return df


def pandas_get_row(db, row):
    line = db.iloc[row]
    return line['fileName'], line['label']

def pandas_file_name_exist(db, name):
    return not db[db['fileName'].isin([name])].empty

def pandas_nonlabeled_exist(db):
    return not db[db['label'].isnull()].empty

def pandas_find_by_file_name(db, fileName):
    findResult = db[db['fileName'].isin([fileName])].reset_index().iloc[0]
    return findResult['index'], findResult['fileName'], findResult['label']

def pandas_find_next_nonlabeled_fileName(db):
    findResult = db[db['label'].isnull()].reset_index().iloc[0]['fileName']
    return findResult

def pandas_write_label_by_file_name(db, fileName, label, user):
    idx, _, _ = pandas_find_by_file_name(db, fileName)
    db.loc[idx, 'label'] = label
    db.loc[idx, 'user'] = user
    return db


def pandas_append_new_row(db, fileName, label, user):
    df = {'fileName': fileName, 'label': label, 'user': user}
    db = db.append(df, ignore_index=True)
    return db

def update_db(dbPath, datasetPath):
    db = pandas_read_csv(dbPath)
    for path in os.listdir(datasetPath):
        if path.endswith('.png') or path.endswith('.jpg'):
            if pandas_file_name_exist(db, path):
                pass
            else:
                db = pandas_append_new_row(db, path, '', '')
                print(path + ' added')
    pandas_save_csv(db, dbPath)