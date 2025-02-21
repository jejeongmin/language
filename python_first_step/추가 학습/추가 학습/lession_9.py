# -*- coding: utf-8 -*-

import feedparser
from optparse import OptionParser

def get_weather():
    parser = feedparser.parse('http://www.kma.go.kr/weather/forecast/mid-term-rss3.jsp?stnId=108')

    # 기상청에서 제공하는 RSS 는 RSS 2.0 형식에 맞게 작성되었으나, 항목이 items 에 들어있는 것이 아니고,
    # content 안에 XML 리스트 형식으로 포함되어 있습니다.
    # 떄문에 feedparser 라이브러리가 아닌 XML 파서를 사용해서 RSS 피드를 분석해야합니다.
    print (parser.feed['title'])
    print (parser.entries[0]['content'][0]['value'])

def get_feed(url):
    # 테스트를 위한 URL
    # - http://api.podty.me/api/v1/share/cast/390937d3e5c758aa6f4005b63542cc83695b4d5e6925fe6a2d4d488d1d05d748/146364
    parser = feedparser.parse(url)

    for i, entity in enumerate(parser.entries):
        if i == 5:
            break

        print (entity.content)
        print ('title : %s' % entity.title)
        print ('link : %s' % entity.enclosures[0].href)
        print ('description : %s' % entity.description)
        print ('publish date : %s' % entity.published)

def main():
    option = OptionParser(usage='%prog', version='%prog 1.0')
    # RSS 피드를 조회할 URL 을 사용자에게 입력받습니다.
    option.add_option('-l', '--link', dest='link', type='string', help='Please enter a link to view')
    # 기상청에서 날씨를 받아오기 위한 옵션으로 -w 를 사용합니다.
    # 기상청의 RSS 는 일반적인 형식과 조금 달라서, 위에서 구현한 로직으로 정상 동작하지 않습니다.
    # 추가로 XML 파서를 사용해서 자세한 정보를 얻어야 하는데, 이번 문제에서는 XML 파서를 사용하는 부분까지는 다루지 않습니다.
    option.add_option('-w', '--weather', dest='weather', action='store_true', help='Search weather condition')

    (options, args) = option.parse_args()

    if options.weather:
        get_weather()
        return

    if options.link is None:
        print ('There is no search link')
        return

    get_feed(options.link)


if __name__ == '__main__':
    main()
