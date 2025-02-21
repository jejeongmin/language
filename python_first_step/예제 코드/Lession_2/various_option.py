# -*- coding: utf-8 -*-

from optparse import OptionParser

def main():
    option = OptionParser(usage='%prog', version='%prog 1.0')

    # default 옵션을 사용해서, 기본 값을 설정합니다.
    option.add_option('-s', '--string', dest='v_str', type='str', default='empty', help='Input string variable with default value.')

    # nargs 옵션을 사용해서, 입력받을 인자의 개수를 설정합니다.
    option.add_option('-i', '--integer', dest='v_ints', type='int', nargs=2, help='Input integer variables.')

    # action 옵션에 'store_true' 나 'store_false' 를 입력해서 변수의 값을 true/false 설정을 합니다.
    option.add_option('-t', '--true', dest='v_true', action='store_true', help='Input boolean(set true) variable.')
    option.add_option('-f', '--false', dest='v_false', action='store_false', help='Input boolean(set false) variable.')

    # callback 옵션과 action 에 'callback' 을 입력해서, 인자 값이 설정됐을 때 호출될 함수를 설정합니다.
    option.add_option('-c', '--call', action='callback', callback=f_callback, help='Call callback function.')

    (options, args) = option.parse_args()

    print ('option 정보 : %s' % options)
    print ('args 정보 : %s' % args)


    # 입력받은 옵션은 다음과 같이 사용합니다.
    if options.v_str:
        print ('-s 옵션에 대한 입력 값 : %s' % options.v_str)

    if options.v_ints:
        print ('-i 옵션에 대한 입력 값 : %s' % (options.v_ints, ))

# callback 옵션으로 호출될 함수의 선언입니다.
# - 함수의 인자 값으로 option, opt, value, parser 를 받아야 합니다.
def f_callback(option, opt, value, parser):
    print ('Call callback function')
    print ('Function parameters | option : %s, opt : %s, value : %s, parser : %s' % (option, opt, value, parser))


if __name__ == '__main__':
    main()
