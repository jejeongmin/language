# -*- coding: utf-8 -*-

import requests
from urllib.parse import quote
from bs4 import BeautifulSoup

SEARCH_URL = "https://www.google.co.kr/search?tbm=nws&q=%s"

def main():
    headers = { 'User-Agent' : 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_14_0) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/69.0.3497.100 Safari/537.36' }

    search_keyword = quote("컴퓨터")
    url = SEARCH_URL % search_keyword

    response = requests.get(url, headers=headers)
    soup = BeautifulSoup(response.text, "html5lib")

    # 기본 예제와 다르게 selecter 의 범위를 넓혀서 많은 범위의 데이터가 나오도록 했습니다.
    items = soup.select("#rso > div > div")

    for item in items:
        # 항목으로 분류하여, 반복문을 돌리고 내부에서 다시 selecter 를 사용해서 범위를 좁힙니다.
        # 구글의 뉴스 페이지는 하나의 selecter 로 모든 값을 추출하기가 어려워서,
        # 조금 번거롭지만 쉬운 방법인 selecter 를 여러번 쓰는 방식으로 정보를 가져왔습니다.
        title = item.select("div > div > h3 > a")
        subject = title[0].text
        link = title[0].get("href")
        print ("%s\n - %s" % (subject, link))

        info = item.select("div > div.gG0TJc > div.slp")
        print ("%s" % info[0].text)

        content = item.select("div > div.gG0TJc > div.st")
        print ("%s" % content[0].text)

        print ("")


if __name__ == '__main__':
    main()
