#-*- coding:UTF-8 -*-
import os

outputStr = ''

def readFile(path, filetype):
    header = []
    myHeader = []
    classCode = []
    code = []
    with open('./code/' + path, 'r', encoding='UTF-8') as f:
        s = f.readline()
        while s is not None and s != '':
            if s.startswith('#ifndef') or s.startswith('#endif'):
                s = f.readline()
                continue
            if s.startswith('#define') and s.strip()[-2:] == '_H':
                s = f.readline()
                continue
            if s.startswith('#include <'):
                header.append(s)
            elif s.startswith('#include "'):
                s = s.split('"')[1].split('.')[0]
                myHeader.append('class ' + s + ';\n')
            elif filetype == 'h':
                classCode.append(s)
            elif filetype == 'cpp':
                code.append(s)
            s = f.readline()
    return [header, myHeader, classCode, code]

def addOutPutStr(addStrList):
    global outputStr
    for i in addStrList:
        outputStr += i

def mergeCode():
    with open('./merge.cpp', 'w') as f:
        f.write(outputStr)

if __name__ == '__main__':
    codeFile = os.listdir("./code")
    headerStrList = []
    myHeaderStrList = []
    classCodeStrList = []
    codeStrList = []
    mainStrList = []

    for i in codeFile:
        if i != 'makefile':
            filetype = i.split('.')[1]
            re = readFile(i, filetype)
            for j in re[0]:
                if j not in headerStrList:
                    headerStrList.append(j)
            for j in re[1]:
                if j not in myHeaderStrList:
                    myHeaderStrList.append(j)
            for j in re[2]:
                classCodeStrList.append(j)
            if i == 'main.cpp':
                mainStrList = re[3]
            else:
                for j in re[3]:
                    codeStrList.append(j)

    addOutPutStr(headerStrList)
    addOutPutStr(myHeaderStrList)
    addOutPutStr(classCodeStrList)
    addOutPutStr(mainStrList)
    addOutPutStr(codeStrList)

    mergeCode()