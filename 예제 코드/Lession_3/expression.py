# -*- coding: utf-8 -*-

# 정규표현식을 사용하기 위해 re 모듈 등록합니다.
import re

def main():

    expr = 'Regular'
    value = 'Regular expression test.'

    # match 와 search 는 비슷한 기능을 합니다.
    # - match 는 문자열의 처음부터 일치하는지를 확인합니다.
    # - search 는 문자열에 검색한 단어가 포함되어있는지를 확인합니다.
    print (bool(re.match(expr, value)))
    print (bool(re.search(expr, value)))

    # 아래 경우, match 를 사용할때는false 가 반환되게 됩니다.
    expr = 'test'
    print (bool(re.match(expr, value)))
    print (bool(re.search(expr, value)))


    # findall 메소드는 검색할 문자가 들어있는 것을 모두 찾아줍니다.
    print (re.findall('te', value))
    print (re.findall('es', value))


    # split 메소드는 표현식에 있는 문자로 구분해서, 리스트로 반환해줍니다.
    expr = '[,; ]+'
    value = 'red blue,green;black'
    print (re.split(expr, value))

    expr = '[,; ]+'
    value = 'red blue,green;;black'
    print (re.split(expr, value))

    expr = '[,; ]'
    value = 'red blue,green;;black'
    print (re.split(expr, value))


    # sub 메소드는 표현식에 있는 형식으로 문자를 변환해줍니다.
    value = 'red blue,green;black'
    print (re.sub(r'[,; ]', ', ', value))

    value = 'Tel : 010-0000-1234'
    print (re.sub(r'\b(\d{3}-\d{4}-\d{4})\b', r'(\1)', value))

    value = 'Tel : 010-0000-1234'
    print (re.sub(r'\b(?P<phone>\d{3}-\d{4}-\d{4})\b', r'(\g<phone>)', value))


    # 표현식을 compile 메소드를 사용해서 저장한 다음 재 사용할 수 있습니다.
    # compile 메소드의 반환 값으로 re 모듈에서 사용하던 메소드를 그냥 사용하실 수 있습니다.
    value = 'Test string for testing regular expressions.'
    c = re.compile('test')
    print (c.findall(value))

    c = re.compile('test', re.I)
    print (c.findall(value))

    value = '010-0000-1234'
    c = re.compile(r'(\d{2,3})-(\d{3,4})-(\d{4})')
    print (c.match(value).groups())

    value = '02-000-1234'
    print (c.match(value).groups())


if __name__ == '__main__':
    main()
