# -*- coding: utf-8 -*-

import os

def main():
    path = './batch_rename'

    # os 하위에 있는 path 모듈의 listdir 메소드를 사용해서, 파일의 존재 유무를 검사합니다.
    for filename in os.listdir(path):
        # listdir 메소드의 반환 값인 파일 이름(string) 변수에 startswith 메소드를 사용하여,
        # 파일 이름이 어떤 문자열로 시작하는지 확인할 수 있습니다.
        if filename.startswith('python_') == False:
            # os.path.join 메소드를 사용하면, path 와 filename 을 조합한 경로를 반환합니다.
            os.rename(os.path.join(path, filename), os.path.join(path, 'python_%s' % filename))


if __name__ == '__main__':
    main()
