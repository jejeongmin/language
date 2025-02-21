# -*- coding: utf-8 -*-

from optparse import OptionParser

def main():
    option = OptionParser(usage='%prog', version='%prog 1.0')

    # OptionParser 의 add_option 메소드를 사용해서, 프로그램에서 사용할 옵션을 등록합니다.
    # - 기본으로 짧은 옵션 문구과 긴 옵션 문구를 입력합니다.
    # - dest 는 사용자에게 입력받을 옵션을 저장할 변수의 이름입니다.
    # - type 은 사용자에게 입력받을 옵션의 자료형입니다.
    # - help 는 사용자에게 보여질 도움말입니다.
    option.add_option('-s', '--string', dest='v_str', type='string', help='Input string variable.')
    option.add_option('-i', '--integer', dest='v_int', type='int', help='Input integer variable.')

    (options, args) = option.parse_args()

    print ('option 정보 : %s' % options)
    print ('args 정보 : %s' % args)


    # 입력받은 옵션은 다음과 같이 사용합니다.
    if options.v_str:
        print ('-s 옵션에 대한 입력 값 : %s' % options.v_str)

    if options.v_int:
        print ('-i 옵션에 대한 입력 값 : %s' % options.v_int)


if __name__ == '__main__':
    main()
