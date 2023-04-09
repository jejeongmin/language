# -*- coding: utf-8 -*-

import os
import glob
from optparse import OptionParser

PATH = './lession_5_sample'
TXT_FILE_PATH = '%s/txt_files/' % PATH

def move_txt_file():
    # glob 모듈을 사용하여, 확장자가 txt 인 파일을 조회합니다.
    for filename in glob.glob(os.path.join(PATH, '*.txt')):
        # 조회된 파일을 rename 메소드를 사용해서 다른 디렉토리로 옮깁니다.
        os.rename(filename, os.path.join(TXT_FILE_PATH, os.path.basename(filename)))

def move_prefix_file(prefix_file_path):
    # listdir 메소드를 사용해서, 디렉토리 안에 있는 파일들을 검색합니다.
    for filename in os.listdir(PATH):
        # startswith 메소드를 사용해서 'python_' 으로 시작하는 파일인 경우, 다른 디렉토리로 이동시킵니다.
        if filename.startswith('python_'):
            os.rename(os.path.join(PATH, filename), os.path.join(prefix_file_path, filename))

def main():
    option = OptionParser(usage='%prog', version='%prog 1.0')
    # prefix 를 구분해서 파일을 이동시킬 폴더를 사용자의 입력 값으로 받습니다.
    option.add_option('-p', '--path', dest='path', type='string', help='Please enter a directory to move.')

    (options, args) = option.parse_args()

    if options.path is not None:
        move_prefix_file(options.path)

    move_txt_file()


if __name__ == '__main__':
    main()
