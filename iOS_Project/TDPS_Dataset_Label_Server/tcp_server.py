import socket
from DatasetLabelServer.PandasOperation import *
import atexit



# dbPath = './Dataset.csv'
# db = pandas_read_csv(dbPath)


files = []
with open('wyh.txt', 'r') as f:
    lines = f.readlines()
    for line in lines:
        files.append(line[:-1])



serverPort = 19999
serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
serverSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
serverSocket.bind(('', serverPort))
serverSocket.listen(1)

print('ready to receive')
while True:
    connectionSocket, addr = serverSocket.accept()
    tcpRequest = connectionSocket.recv(1024).decode()
    if tcpRequest == '0':
        print(len(files))
        fn = files.pop()
        connectionSocket.send(fn.encode())
    else:
        pass
    connectionSocket.close()
