import socket
import random

def genFileName():
    return random.choice(['1.png', '2.png'])

serverPort = 1999
serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
serverSocket.bind(('', serverPort))
serverSocket.listen(1)
print('ready to receive')
while True:
    connectionSocket, addr = serverSocket.accept()
    tcpRequest = connectionSocket.recv(1024).decode()
    if tcpRequest == '0':
        connectionSocket.send(genFileName().encode())
    else:
        fileName, labelResult = tcpRequest.split()
        print(fileName + ' label is ' + labelResult)
    connectionSocket.close()
