import socket
serverName = 'pscpeng.xyz'
serverPort = 1999
requestName = True
fileNameRequest = '0'
fileName = '0025323.jpg L01 wyh'
clientSoccket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
clientSoccket.connect((serverName, serverPort))
clientSoccket.send(fileName.encode())
clientSoccket.close()

