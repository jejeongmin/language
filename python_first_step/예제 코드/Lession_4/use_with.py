# -*- coding: utf-8 -*-

def use_read():
    # with 구문을 사용해서, 코드를 간단히 바꿀 수 있습니다.
    # close 구문을 생략하고, 사용할 수 있습니다.
    with open('./test_file', 'r') as f:
        print (f.read())

def use_readline():
    with open('./test_file', 'r') as f:
        while True:
            line = f.readline()

            if not line:
                break

            print (line)

def use_readlines():
    with open('./test_file', 'r') as f:
        print (f.readlines())

def use_write():
    with open('./write_test', 'w') as f:
        f.write('python3\n')
        f.write('write test\n')

def use_write_with_append():
    with open('./write_test', 'w') as f:
        f.write('appended line\n')

def main():
    use_read()
    print ('================')
    use_readline()
    print ('================')
    use_readlines()


if __name__ == '__main__':
    main()
