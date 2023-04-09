# -*- coding: utf-8 -*-

import os

def main():
    # os 하위에 있는 path 모듈의 isdir 메소드를 사용해서, 디렉토리의 존재 유무를 검사합니다.
    if os.path.isdir('./sample_dir'):
        os.rename('./sample_dir', './SAMPLE_DIR')


if __name__ == '__main__':
    main()
