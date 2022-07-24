import socket
from PandasOperation import *
import time


def tcp_server_full_function():
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
        elif tcpRequest.startswith('progress'):
            _, userName = tcpRequest.split()
            progress = os.popen('cat /root/Server-Apps/DatasetLabelServer/Dataset.csv | grep ' + userName + '| wc -l').read()
            # progress = os.popen('ls | wc -l').read()

            connectionSocket.send(progress.encode())
        else:
            fileName, labelResult, user = tcpRequest.split()
            if labelResult == 'redo':
                labelResult = ''
                user = ''
            db = pandas_write_label_by_file_name(db, fileName, labelResult, user)
            pandas_save_csv(db, dbPath)
            print(fileName + ' is labeled ' + labelResult + ' by ' + user + ' at ' + time.strftime("%Y-%m-%d %H:%M:%S",
                                                                                                   time.localtime()))
        connectionSocket.close()
