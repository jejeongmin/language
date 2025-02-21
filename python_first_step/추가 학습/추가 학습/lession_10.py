# -*- coding: utf-8 -*-

import requests
from urllib.parse import quote
from bs4 import BeautifulSoup
from optparse import OptionParser

# 변경된 검색 URL 조건에 맞게 URL 을 설정합니다.
SEARCH_URL = "https://www.google.co.kr/search?tbm=nws&q=%s&num=%s%s"

def scraping(keyword, num, time):
    headers = { 'User-Agent' : 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_14_0) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/69.0.3497.100 Safari/537.36' }
    # 변경된 검색 URL 조건에 맞게 입력 값을 설정합니다.
    url = SEARCH_URL % (quote(keyword), num, time)

    response = requests.get(url, headers=headers)

    soup = BeautifulSoup(response.text, "html5lib")

    titles = soup.select("#rso > div > div > div > div > h3 > a")

    for title in titles:
        subject = title.text
        link = title.get("href")
        print ("%s\n - %s" % (subject, link))

def get_time(time):
    # 검색할 뉴스의 기간을 설정하는 부분으로 구글에서는 다음과 같이 설정합니다.
    # - tbs=qdr:X
    # - X 에 들어갈 단어는 h, d, w, m 으로 각각 1시간, 1일, 1주일, 1개월을 의미합니다.
    if time is 'h':
        return '&tbs=qdr:h'
    elif time is 'd':
        return '&tbs=qdr:d'
    elif time is 'w':
        return '&tbs=qdr:w'
    elif time is 'm':
        return '&tbs=qdr:m'
    else:
        return ''

def main():
    option = OptionParser(usage='%prog', version='%prog 1.0')
    # 검색할 단어를 사용자에게 입력받습니다.
    option.add_option('-k', '--keyword', dest='keyword', type='string', help='Please enter a search keyword.')
    # 검색할 뉴스의 개수를 사용자에게 입력받습니다.
    option.add_option('-n', '--num', dest='num', type='int', help='Please enter a number of search result.')
    # 검색할 기간을 사용자에게 입력받습니다.
    option.add_option('-t', '--time', dest='time', type='string', help='Please enter a search time (h, d, w, m)')

    (options, args) = option.parse_args()

    if options.keyword is None:
        print ('No input keyword')
        return

    # 검색한 뉴스의 개수의 입력이 없는 경우, 기본으로 10 개의 뉴스를 검색합니다.
    num = 10
    if options.num is not None:
        num = options.num

    # 검색할 뉴스의 기간이 없는 경우, 조건을 설정하지 않습니다.
    time = ''
    if options.time is not None:
        time = get_time(options.time)

    scraping(options.keyword, num, time)


if __name__ == '__main__':
    main()
