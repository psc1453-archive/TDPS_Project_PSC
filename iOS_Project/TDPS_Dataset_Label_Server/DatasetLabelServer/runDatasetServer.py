import socket
from PandasOperation import *


def runDatasetServer():
    dbPath = './Dataset.csv'
    db = pandas_read_csv(dbPath)

    serverPort = 1999
    serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    serverSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    serverSocket.bind(('', serverPort))
    serverSocket.listen(1)

    print('ready to receive')
    while True:
        connectionSocket, addr = serverSocket.accept()
        tcpRequest = connectionSocket.recv(1024).decode()
        if tcpRequest == '0':
            connectionSocket.send(genFileName(db).encode())
        else:
            fileName, labelResult, user = tcpRequest.split()
            if labelResult == 'redo':
                labelResult = ''
                user = ''
            db = pandas_write_label_by_file_name(db, fileName, labelResult, user)
            pandas_save_csv(db, dbPath)
            print(fileName + ' label is ' + labelResult)
        connectionSocket.close()