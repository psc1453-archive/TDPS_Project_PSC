import os
wrongCheckList = ""
with open('wrong.txt', 'r') as wrongList:
    wrongImgs = wrongList.readlines()
    for wrongPic in wrongImgs:
        wrongCheckList = wrongCheckList + '|' + wrongPic[:-1]
# print(wrongCheckList)
os.system('cat Dataset.csv | egrep \'' + wrongCheckList + '\' > wrongResult.txt')
