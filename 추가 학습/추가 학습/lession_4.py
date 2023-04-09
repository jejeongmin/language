# -*- coding: utf-8 -*-

import re
import fileinput

def markCredentialNumber(line):
    # 주민 등록 정규식 분석
    # 'r' : raw string 이라는 뜻으로 '\n', '\t' 와 같은 문자를 특수문자로 처리하지 않고, 문자 그대로 처리합니다.
    # '?:' : Non-capturing 문자로 이 조건과 뒤에 나오는 다른 조건이 맞아야지 정규 표현식에서 걸러집니다.
    #        예를 들어 아래 정규 표현식에서 맨처음의 '?:' 를 제거하고 실행하면, 주민등록 번호의 앞부분만 정규 표현식으로 검출됩니다.
    # [0-9]{2} : 주민등록번호의 년도에 해당하는 부분으로 00 년생부터 99년생까지 확인합니다.
    # (0[1-9]|1[0-2]) : 주민등록번호의 월에 해당하는 부분으로 0[1-9] 나 1[0-2] 의 조건 중 하나라도 만족하면 됩니다.
    #                   즉, 01 부터 09 까지 그리고, 10 에서 12 까지 검출합니다.
    # (0[1-9]|[1,2][0-9]|3[0,1]) : 주민등록번호의 일에 해당하는 부분으로 0[1-9] 나 [1,2][0-9], 3[0,1] 의 조건 중 하나라도 만족하면 됩니다.
    #                              즉, 01 부터 09, 10 부터 29, 30 부터 31 까지 검출합니다.
    #
    # '-' : 주민등록번호에서 앞번호와 뒷번호를 구분하기 위해 사용합니다.
    # [1-4][0-9]{6} : 주민등록번호의 뒷자리에 해당하는 값으로 맨 처음 숫자는 1~4 까지, 그리고 뒤에 6 개의 숫자가 포함되어 총 7 자리를 구성합니다.
    #
    #
    # 변환식 분석
    # 정규 표현식에서 검출된 group 중, 첫번째 부분(주민등록번호의 앞부분)이 \g<1> 에 적히고,
    # 다음으로 구분자인 '-' 를 적어준다음 나머지 뒷 자리 7 자리를 '*' 로 표시합니다.
    # 정규 표현식을 조금 수정하고, 변환식의 그룹을 조정하면, 뒷 자리의 앞 한자리까진 출력하고, 나머지 6 자리를 * 로 변경할 수도 있습니다.
    changed_line = re.sub(
                    r'([0-9]{2}(?:0[1-9]|1[0-2])(?:0[1-9]|[1,2][0-9]|3[0,1]))-[1-4][0-9]{6}',
                    r'\g<1>-*******',
                    line
                    )
    return line.replace(line, changed_line)

def convertLanguage(line):
    # 간단하게 replace 명령을 사용해서 변환할 수 있습니다.
    # 이때, 대소문자 상관없이 모든 문자를 변경하기 위해 미리 소문자나 대문자로 변경한 다음 변환합니다.
    # 이럴 경우, 기존의 대문자로 작성되거나 소문자로 작성된 문자가 대소문자만 변경될 수 있으니,
    # 원래 ㅁ구문과 비교하여 달라진 것이 있을 때만 변환해서 반환하게 합니다.
    changed_line = line.lower().replace('test', '테스트')
    if changed_line == line.lower():
        return line

    return line.replace(line, changed_line)

def changeFileText():
    with fileinput.FileInput('./lession_4_sample', inplace=True) as f:
        for line in f:
            changed_line = markCredentialNumber(line)
            changed_line = convertLanguage(changed_line)
            print (line.replace(line, changed_line), end='')

def readFile():
    print ('==================')
    with open('./lession_4_sample', 'r') as f:
        print (f.read())
    print ('==================')

def main():
    readFile()
    changeFileText()
    readFile()


if __name__ == '__main__':
    main()
