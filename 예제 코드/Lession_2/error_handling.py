# -*- coding: utf-8 -*-

from optparse import OptionParser, OptionValueError

def main():
    option = OptionParser(usage='%prog', version='%prog 1.0')

    option.add_option('-t', '--true', dest='v_true', action='store_true', help='Input boolean(set true) variable.')
    option.add_option('-f', '--false', dest='v_false', action='store_false', help='Input boolean(set false) variable.')
    option.add_option('-c', '--call', action='callback', callback=f_callback, help='Call callback function.')

    (options, args) = option.parse_args()

    # -t 옵션과 -f 옵션은 같이 사용할 수 없다는 것을 가정합니다.
    # - callback 함수가 아닌 경우, if 문을 사용해서 예외처리를 합니다.
    if options.v_true is not None and options.v_false is not None:
        print ("Can't use -t and -f.")

def f_callback(option, opt, value, parser):
    print ('Call callback function')
    print ('Function parameters | option : %s, opt : %s, value : %s, parser : %s' % (option, opt, value, parser))

    # -t 옵션과 -f 옵션은 같이 사용할 수 없다는 것을 가정합니다.
    # - callback 함수 안에서는 raise 를 사용해서 오류를 호출합니다.
    if parser.values.v_true is not None and parser.values.v_false is not None:
        raise OptionValueError("Can't use -t and -f before -c")


if __name__ == '__main__':
    main()
