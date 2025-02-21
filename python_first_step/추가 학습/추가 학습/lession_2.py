# -*- coding: utf-8 -*-

from optparse import OptionParser, OptionValueError

def main():
    option = OptionParser(usage='%prog', version='%prog 1.0')

    option.add_option('-t', '--true', dest='v_true', action='store_true', help='Input boolean(set true) variable.')
    option.add_option('-f', '--false', dest='v_false', action='store_false', help='Input boolean(set false) variable.')

    (options, args) = option.parse_args()

    # 인자 값의 개수를 검증하는 것은 option.parse_args 반환 값 중, 두번째 값을 통해서 할 수 있습니다.
    # 이 값은 option 에 등록되지 않은 인자 값들을 가지고 있습니다.
    # 그래서, 이 값을 len 로 확인하면 인자 값의 개수가 나오게 됩니다.
    print ("Count of argument : %s" % len(args))

    # 베타적인 명령의 경우, 별도의 예외처리를 해줘야하고, 그외의 타입 오류는 optparse 라이브러리에서
    # 자동으로 생성을 해줍니다.
    if options.v_true is not None and options.v_false is not None:
        print ("Can't use -t and -f.")


if __name__ == '__main__':
    main()
