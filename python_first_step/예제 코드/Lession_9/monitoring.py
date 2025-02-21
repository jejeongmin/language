# -*- coding: utf-8 -*-

import wget
import feedparser

# 주기적으로 새로운 팟캐스트가 있는지 확인하기 위해 동작을 일시 중지하는 sleep 메소드를 사용합니다.
from time import sleep

# 마지막으로 받아온 팟캐스트의 이름을 기록하기 위해 변수를 선언합니다.
saved_title = ''

def check_new_title():
    # global 키워드를 사용해서, 앞서 정의한 saved_title 변수를 사용하겠다고 선언합니다.
    # global 키워드를 사용하지 않고, saved_title 을 사용하면 사용하는 환경에 따라서
    # 새로운 변수로 saved_title 을 생성할 수 있습니다. 그렇게 되면, 항상 새로운 팟캐스트로 인식해서
    # 계속 다운로드를 받으려 할 수 있습니다.
    global saved_title
    url = 'http://api.podty.me/api/v1/share/cast/390937d3e5c758aa6f4005b63542cc83695b4d5e6925fe6a2d4d488d1d05d748/146364'
    parser = feedparser.parse(url)

    # 팟캐스트를 조회하고, 다운로드 받는 코드는 기존과 동일합니다.
    # 다만, 이미 저장한 최신 팟캐스트의 이름과 동일하면, 다운받지 않습니다.
    if parser.entries[0].title == saved_title:
        print ('There is no new podcast')
        return
    else:
        saved_title = parser.entries[0].title
        print ('New podcast!! : %s' % parser.entries[0].title)
        print ('Downloading...')
        wget.download(parser.entries[0].enclosures[0].href, './')
        print ('\nDone')

def main():
    # 무한으로 반복하며, 새로운 팟캐스트가 있는지 검사하고, 다운로드 받습니다.
    # 매순간 실행하면, 컴퓨터에 부하를 주게 되니, sleep 메소드를 사용해서 10분(600초)에 한번 조회하도록 했습니다.
    while True:
        check_new_title()
        sleep (600)


if __name__ == '__main__':
    main()
