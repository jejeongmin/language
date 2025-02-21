# -*- coding: utf-8 -*-

def use_read():
    # 'r' 옵션을 사용해서, 읽기 모드로 파일을 엽니다.
    f = open('./test_file', 'r')
    # 한번에 파일에 있는 모든 내용을 읽고 반환하는 메소드
    print (f.read())
    f.close()

def use_readline():
    # 'r' 옵션을 사용해서, 읽기 모드로 파일을 엽니다.
    f = open('./test_file', 'r')
    while True:
        # 한번에 하나의 라인만 읽고 반환하는 메소드
        line = f.readline()

        if not line:
            break

        print (line)

    f.close()

def use_readlines():
    # 'r' 옵션을 사용해서, 읽기 모드로 파일을 엽니다.
    f = open('./test_file', 'r')
    # 파일을 라인 별로 분리해서 한번에 반환하는 메소드
    print (f.readlines())
    f.close()

def use_write():
    # 'w' 옵션을 사용해서, 쓰기 모드로 파일을 엽니다.
    # 기존에 저장된 내용은 덮어 씌워집니다.
    f = open('./write_test', 'w')
    f.write('python3\n')
    f.write('write test\n')
    f.close()

def use_write_with_append():
    # 'a' 옵션을 사용해서, 쓰기 모드로 파일을 엽니다.
    # 기존에 저장된 내용에 추가로 내용이 작성됩니다.
    f = open('./write_test', 'a')
    f.write('appended line\n')
    f.close()

def main():
    use_read()
    print ('================')
    use_readline()
    print ('================')
    use_readlines()

    use_write()
    use_write_with_append()


if __name__ == '__main__':
    main()
