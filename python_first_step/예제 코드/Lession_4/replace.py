# -*- coding: utf-8 -*-

import re
import fileinput

def convertToLowerCase():
    # FileInput 메소드를 사용해서, 파일을 읽음과 동시에 수정할 수 있습니다.
    # 읽고 수정하려면, inplace 옵션을 사용해야합니다. 기본 값은 false 인데,
    # true 로 변경하면 작업할 때 자동으로 백업 파일이 생성됩니다.
    # 백업 파일을 따로 두고, 파일을 수정한 다음 수정이 완료되면,
    # 백업 파일을 변경하는 형태로 동작합니다.
    #
    # backup 옵션을 줘서, 백업 파일의 이름을 변경할 수도 있습니다.
    # 이름이 변경된 경우에는 백업 파일을 자동으로 삭제하지 않습니다.
    # 백업 파일의 이름을 ".bak" 로 하면, 수정이 완료된 뒤, 백업본이 자동으로 삭제됩니다.
    with fileinput.FileInput('./replace_test_file', inplace=True) as f:
        for line in f:
            print (line.replace(line, line.lower()), end='')

def convertToUpperCaseWithRe():
    with fileinput.FileInput('./replace_test_file', inplace=True) as f:
        for line in f:
            print (line.replace(line, re.sub('sample', 'Sample', line)), end='')

def readFile():
    print ('==================')
    with open('./replace_test_file', 'r') as f:
        print (f.read())
    print ('==================')

def main():
    readFile()
    convertToLowerCase()
    readFile()
    convertToUpperCaseWithRe()
    readFile()


if __name__ == '__main__':
    main()
