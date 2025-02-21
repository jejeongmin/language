# -*- coding: utf-8 -*-

import os
import glob


def main():
    path = './extension'
    # glob 모듈의 glob 메소드를 사용해서, 특정 파일의 확장자를 가진 파일의 목록을 반환 받을 수 있습니다.
    for filename in glob.glob(os.path.join(path, '*.txt')):
        print (filename)


if __name__ == '__main__':
    main()
