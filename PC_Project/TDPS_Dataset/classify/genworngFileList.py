import os
wrongCheckList = ""
with open('wrong.txt', 'r') as wrongList:
    wrongImgs = wrongList.readlines()
    for wrongPic in wrongImgs:
        wrongCheckList = wrongCheckList + "{:0>7s}".format(wrongPic[:-1]) + '.jpg\n'
f = open('genWrongList.txt', 'a+')
f.write(wrongCheckList)
# os.system('cat Dataset.csv | egrep \'' + wrongCheckList + '\' > wrongResult.txt')