# -*- coding: utf-8 -*-

from optparse import OptionParser

def main():
    # '%prog' 는 실행한 파일의 이름으로 대치됩니다.
    option = OptionParser(usage='%prog', version='%prog 1.0')

    # parse_args() 를 호출해서, 사용자가 입력한 옵션을 파싱(Parsing) 합니다.
    # - 반환되는 첫번째 값인 options 에는 등록된 옵션에 대한 정보가 저장됩니다.
    # - 반환되는 두번째 값인 args 에는 등록된 옵션 외의 다른 인자 값에 대한 정보가 출력됩니다.
    (options, args) = option.parse_args()


if __name__ == '__main__':
    main()
