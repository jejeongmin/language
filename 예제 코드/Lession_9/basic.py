# -*- coding: utf-8 -*-

# RSS 를 다루기 위한 라이브러리입니다.
import feedparser

def main():
    # 예제에서 사용할 팟캐스트의 RSS 주소입니다.
    # - podty 라는 팟캐스트 서비스의 지대넓얕이라는 팟캐스트입니다.
    url = 'http://api.podty.me/api/v1/share/cast/390937d3e5c758aa6f4005b63542cc83695b4d5e6925fe6a2d4d488d1d05d748/146364'

    # feedparser 의 parse 메소드를 사용하면, RSS 를 파싱한 결과를 얻을 수 있습니다.
    parser = feedparser.parse(url)

    # 파싱된 결과는 다음과 같이 확인할 수 있습니다.
    # 먼저, 팟캐스트에 전반적인 설명은 parser.feed 에 저장되어있습니다.
    # parser.feed 는 사전을 기반으로 한 자료형으로 JSON 데이터를 사전과 동일한 방식으로 조회할 수 있도록 해줍니다.
    # feed 로는 title, title_detail, tags, author, links, summary 등의 정보를 조회 할 수 있습니다.
    print (parser.feed['title'])

    # 실제 팟캐스트의 항목을 하나하나 살펴보려면, parser.entries 를 사용합니다.
    # parser,entries 는 리스트 형태의 자료형으로, 이 안에 팟캐스트 파일 하나하나의 정보가 담겨져 있습니다.
    # entries 안의 정보는 사전 형태의 자료형으로 사전에서 값을 조회하듯이 사용할 수도 있고,
    # 아래와 같이 사용할 수도 있습니다.
    # 조회할 수 있는 값은 팟캐스트의 RSS 구성 형태에 따라 다릅니다.
    # 이 부분은 사용할 RSS 주소의 구성을 먼저 확인하신후, 작업해주시면 됩니다.
    for entity in parser.entries:
        print ('title : %s' % entity.title)
        print ('link : %s' % entity.enclosures[0].href)
        print ('description : %s' % entity.description)
        print ('publish date : %s' % entity.published)


if __name__ == '__main__':
    main()
