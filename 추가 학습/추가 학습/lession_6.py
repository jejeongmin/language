# -*- coding: utf-8 -*-

import os
import piexif
from PIL import Image
from PIL.ExifTags import TAGS

def crop(img):
    # 사진을 자를 크기를 입력합니다.
    # "왼쪽, 윗쪽, 오른쪽, 아래쪽" 순서로 입력합니다.
    # - 좌표의 크기로, 왼쪽과 윗쪽이 각각 오른쪽과 아래쪽보다 크거나 같을 수 없습니다.
    size = (0, 0, 400, 400)

    # crop 메소드를 사용해서 크기를 자릅니다.
    cropped_img = img.crop(size)

    # show 메소드를 사용해서 이미지를 띄웁니다.
    cropped_img.show()

def print_exif(img):
    # EXIF 정보를 출력해주는 함수입니다.
    exif = img._getexif()
    if exif is None:
        print ('There is no exif data')
        return

    print (exif)
    for k, v in exif.items():
        print ('%s : %s' % (k, v))

def insert_exif(img):
    # EXIF 정보가 삽입될 사진 파일의 이름입니다.
    manufacture_img = './manufacture_exif.jpg'

    try:
        # EXIF 정보를 가져올 파일의 정보입니다.
        exif_img = Image.open('./lession_6_sample_with_exif.jpg')

        # EXIF 정보는 정교한 정보로 별도의 형식에 맞춰서 입력해야합니다.
        # 임의로 삽입할 수도 있지만, 예제에서는 간편하게 다른 사진의 EXIF 정보를 불러와서 다른 사진에
        # 삽입하도록 했습니다.
        # EXIF 정보를 불러오기 위해 piexif 라는 라이브러리를 사용해서 exif 정보를 사전 형태로 가져옵니다.
        exif_dic = piexif.load(exif_img.info['exif'])

        # 사전 형태로 가져온 exif 정보를 piexif 의 dump 명령을 사용해서 저장합니다.
        # 이 과정에서 exif 의 사전 내용을 변경하여 저장할 수도 있습니다.
        img.save(manufacture_img, 'JPEG', quality=100, exif=piexif.dump(exif_dic))
    except IOError:
        print ('Can not create file')


    print_exif(Image.open(manufacture_img))


if __name__ == '__main__':
    img_name = './lession_6_sample.jpg'
    img = Image.open(img_name)

    print_exif(img)
    insert_exif(img)
    crop(img)
