import socket
serverName = '127.0.0.1'
serverPort = 12001
requestName = True
fileNameRequest = '0'
fileName = ''
for i in range(1,5):
    clientSoccket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    clientSoccket.connect((serverName, serverPort))

    if requestName:
        clientSoccket.send(fileNameRequest.encode())
        fileName = clientSoccket.recv(1024).decode()
        print(fileName)

    else:
        labelResult = input('Please label\n')
        clientSoccket.send((fileName + ' ' + labelResult).encode())
        feedback = clientSoccket.recv(1024).decode()
        print(feedback)
    clientSoccket.close()
    requestName = not requestName






