# -*- coding: utf-8 -*-

import os

def main():
    # os 하위에 있는 path 모듈의 isfile 메소드를 사용해서, 파일의 존재 유무를 검사합니다.
    # 또, os 하위에 있는 rename 메소드를 사용해서, 파일의 이름을 변경합니다.
    if os.path.isfile('./sample'):
        os.rename('./sample', './SAMPLE')


if __name__ == '__main__':
    main()
