# -*- coding: utf-8 -*-

def main():

    # 문자열의 대소문자를 조작하는 간단한 메소드들
    print ('=============================')
    test_str = 'Test String 1234 !@#$'
    print ('plain: %s' % test_str)
    print ('upper: %s' % test_str.upper())
    print ('lower: %s' % test_str.lower())
    print ('lower with capitalize: %s' % test_str.lower().capitalize())
    print ('lower with title: %s' % test_str.lower().title())
    print ('=============================\n')


    # 특정 문자의 인덱스나 개수를 가져오는 메소드들
    print ('\n=============================')
    test_str = 'Test String 1234 !@#$'
    print ('count "t": %s' % test_str.count('t'))
    print ('index "t": %s' % test_str.index('t'))
    print ('=============================\n')


    # 문자열의 속성을 확인하는 메소드들
    print ('\n=============================')
    space_str = '   '
    str_str = 'TestString'
    str_with_space_str = 'Test String'
    int_str = '123'
    float_str = '123.45'
    print ('plain: %s' % str_str)
    print ('isspace: %s' % str_str.isspace())
    print ('isalpha: %s' % str_str.isalpha())
    print ('isalnum: %s' % str_str.isalnum())
    print ('')
    print ('plain: %s' % str_with_space_str)
    print ('isspace: %s' % str_with_space_str.isspace())
    print ('isalpha: %s' % str_with_space_str.isalpha())
    print ('isalnum: %s' % str_with_space_str.isalnum())
    print ('')
    print ('plain: %s' % space_str)
    print ('isspace: %s' % space_str.isspace())
    print ('isalnum: %s' % space_str.isalnum())
    print ('')
    print ('plain: %s' % int_str)
    print ('isdigit: %s' % int_str.isdigit())
    print ('isdecimal: %s' % int_str.isdecimal())
    print ('isalnum: %s' % int_str.isalnum())
    print ('')
    print ('plain: %s' % float_str)
    print ('isdigit: %s' % float_str.isdigit())
    print ('isdecimal: %s' % float_str.isdecimal())
    print ('isalnum: %s' % float_str.isalnum())
    print ('=============================\n')


    # 문자열의 공백을 제거하는 메소드들
    print ('\n=============================')
    test_str = ' Test String 1234 !@#$ '
    print ('plain: %s' % test_str)
    print ('lstrip: %s' % test_str.lstrip())
    print ('rstrip: %s' % test_str.rstrip())
    print ('strip: %s' % test_str.strip())
    print ('=============================\n')


    # 문자열을 특정 문자를 기준으로 분리하는 메소드들
    print ('\n=============================')
    test_str = ' Test String 1234 !@#$ '
    print ('plain: %s' % test_str)
    print ('split: %s' % test_str.split(' '))

    test_str = '''
        1st test world
        2st test world
    '''
    print ('plain: %s' % test_str)
    print ('splitlines: %s' % test_str.splitlines())
    print ('=============================\n')


    # 문자열을 특정 문자열로 치환하는 메소드
    print ('\n=============================')
    test_str = 'red blue black yellow'
    print ('plain: %s' % test_str)
    print ('replace: %s' % test_str.replace('black', 'green'))
    print ('replace: %s' % test_str.replace('yellow', ''))

    test_str = ' Test String 1234 !@#$ '
    print ('plain: %s' % test_str)
    print ('replace: %s' % test_str.replace(' ', ''))
    print ('=============================\n')


if __name__ == '__main__':
    main()
