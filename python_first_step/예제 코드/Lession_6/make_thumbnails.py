# -*- coding: utf-8 -*-

import os
from PIL import Image

def main():
    size = (512, 512)
    img_file = 'wallpaper_2.jpg'

    f = ('%s_resized.%s' % (os.path.splitext(img_file)[0], 'jpg'))
    try:
        img = Image.open(img_file)
        # thumbnail 메소드를 사용해서, 이미지의 크기를 변경합니다.
        img.thumbnail(size)
        # 변경된 이미지 파일을 save 메소드를 사용해서 저장합니다.
        img.save(f, 'JPEG', quality=100)
    except IOError:
        print ('Can not create thumbnail for %s' % img_file)


if __name__ == '__main__':
    main()
