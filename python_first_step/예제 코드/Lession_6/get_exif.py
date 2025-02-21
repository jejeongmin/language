# -*- coding: utf-8 -*-

import os
from PIL import Image

# PIL 모듈의 ExifTags 에는 이용할 수 있는 두가지 TAG 가 있습니다.
# 모두, 사전 형식의 미리 정의된 값으로, 사진의 EXIF 속성 정보를 조회하는데 사용됩니다.
# - GPSTAGS 는 사진의 GPS 정보를 담고 있습니다.
# - TAGS 는 사진의 일반적인 정보를 담고 있습니다.
from PIL.ExifTags import TAGS
from PIL.ExifTags import GPSTAGS


def get_exif_info():
    img_file = 'osaka.jpg'
    img = Image.open(img_file)

    # _getexif 메소드를 사용해서, 이미지 속성을 담고 있는 사전 객체를 반환 받습니다.
    # 반환 값이 None 이면, 이 사진은 EXIF 정보를 가지고 있지 않은 것입니다.
    exif = img._getexif()
    if exif is None:
        print ('There are no exif information in the photo.')
        return

    exif_data = {}
    for tag_id, tag_value in exif.items():
        # TAGS 사전에서 tag_id 로 값을 조회하고, 값이 없는 경우 tag_id 를 반환합니다.
        tag = TAGS.get(tag_id, tag_id)

        # tag 의 정보가 GPSInfo 라면, GPSTAGS 사전에서 다시 정보를 검색합니다.
        if tag == 'GPSInfo':
            gps_data = {}
            for gps_id in tag_value:
                gps_tag = GPSTAGS.get(gps_id, gps_id)
                gps_data[gps_tag] = tag_value[gps_id]

            exif_data[tag] = gps_data
        else:
            exif_data[tag] = tag_value

    return exif_data

def print_exif_info(exif_data):
    # 추출한 사전 정보를 출력하는 부분입니다.
    for key, value in exif_data.items():
        if type(value) is dict:
            for sub_key, sub_value in value.items():
                print ('%s : %s' % (sub_key, sub_value))

            continue

        print ('%s : %s' % (key, value))

def main():
    print_exif_info(get_exif_info())


if __name__ == '__main__':
    main()
