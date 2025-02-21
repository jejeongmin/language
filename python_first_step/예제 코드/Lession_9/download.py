# -*- coding: utf-8 -*-

# URL 로 파일을 다운받기 위한 라이브러리 입니다.
import wget
import feedparser

def main():
    url = 'http://api.podty.me/api/v1/share/cast/390937d3e5c758aa6f4005b63542cc83695b4d5e6925fe6a2d4d488d1d05d748/146364'
    parser = feedparser.parse(url)

    print (parser.feed['title'])
    # 예제에서는 모든 팟캐스트 데이터를 다운 받을수는 없으니, 3개의 파일만 다운 받도록 구성했습니다.
    # enumerate 를 사용하면, index 를 자동으로 계산해서 변수에 담아줍니다.
    for i, entity in enumerate(parser.entries):
        if i == 3:
            break

        print ('title : %s' % entity.title)
        print ('link : %s' % entity.enclosures[0].href)
        print ('description : %s' % entity.description)
        print ('publish date : %s' % entity.published)

        # 앞서 정보를 조회하는 부분은 기존 예제와 동일합니다.
        # 추가된 부분은 아래 wget 라이브러리를 사용해서 팟캐스트를 download 를 받는 부분입니다.
        # 파일을 다운받는 여러가지 방법이 있지만, wget 라이브러리를 사용하면 간단하게 파일을 다운받을 수 있습니다.
        # download 메소드의 인자로 파일을 다운받을 주소와, 다운받을 위치를 넘겨주면 됩니다.
        wget.download(entity.enclosures[0].href, './')


if __name__ == '__main__':
    main()
