# -*- coding: utf-8 -*-

import datetime

def main():

    # 간단한 문자열 출력
    print ('Basic format : %s, %s, %s' % (1, 2, 'test'))

    # format 메소드를 이용한 문자열 출력
    print ('Use format method : {0} {1} {2}'.format(1, 2, 'test'))
    print ('Use format method(reverse) : {2} {1} {0}'.format(1, 2, 'test'))

    # format 메소드와 이름을 이용한 문자열 출력
    print ('Use format method with name : {first} {second} {text}'.format(first=1, second=2, text='test'))

    # 문자열 정렬
    print ('{:<50}'.format('left aligned'))
    print ('{:>50}'.format('right aligned'))
    print ('{:^50}'.format('centered'))

    # 숫자의 자료형 변환
    print ('int : {0:d}, hex : {0:x}, oct : {0:o}, bin : {0:b}'.format(10))

    # 천 단위의 , 출력
    print ('{:,}'.format(1234567890))

    # % 사용
    print ('Percent : {:.1%}'.format(25/100))

    # 시간 출력
    d = datetime.datetime(2018, 10, 7, 14, 30, 58)
    print ('{:%Y-%m-%d %H:%M:%S}'.format(d))


if __name__ == '__main__':
    main()
