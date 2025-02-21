# -*- coding: utf-8 -*-

# PIL 모듈을 Fork 한 Pillow 모듈을 사용합니다.
# 설치시의 이름은 Pillow 지만, 사용할 때는 PIL 로 사용합니다.
from PIL import Image

def main():
    # Pillow 의Image 모듈을 사용해서 이미지 파일을 불러옵니다.
    im = Image.open('./wallpaper_1.jpg')

    # Image 파일을 통해 불러온 이미지는 가지고 있는 정보를
    # 조회하는 것뿐 만 아니라 이미지를 조작을 할 수 있습니다.
    # - format 을 사용하면, 이미지 파일의 속성(jpeg, png 등)을 알 수 있습니다.
    # - size 를 사용하면, 이미지 파일의 크기를 알 수 있습니다.
    # - mode 를 사용하면, 이미지 픽셀의 형식(RGB, CMYK 등)을 알 수 있습니다.
    # 이 밖에도 filename, draft, getcolors, getpixel, histogram, resize, split, thumbnail, transform 등의
    # 정보 조회와 이미지 조작 메소드 등을 사용할 수 있습니다.
    print(im.format, im.size, im.mode)

    # show 메소드를 사용하면, 이미지 파일을 화면에 보여줍니다.
    im.show()

if __name__ == '__main__':
    main()
