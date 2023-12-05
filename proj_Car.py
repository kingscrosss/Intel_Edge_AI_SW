import numpy as np
import cv2
from PIL import Image
import pytesseract
import re

import time
import uuid
import json
import requests

################################ 이미지파일 흑백으로 변환 ################################
file_path = './datasets/car_num11'
img = cv2.imread(file_path+'.jpg')
img_copy = img.copy()
imgray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
dst = cv2.GaussianBlur(imgray, (3,3), 0)
ret, thimg = cv2.threshold(dst, 180, 255, cv2.THRESH_BINARY | cv2.THRESH_OTSU)
# ret, thimg = cv2.threshold(dst, 180, 255, 0)
contours, _ = cv2.findContours(thimg, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
cv2.drawContours(img, contours, -1, (0,255,255), 1)

################################ 이미지 중 번호판 찾아 추출 ################################
img_h, img_w, c = img.shape # height, width, channel
MIN_AREA = 1000
MIN_WIDTH, MIN_HEIGHT=2,8
MAX_WIDTH, MAX_HEIGHT=img_w,img_h
MIN_RATIO, MAX_RATIO = 3,6
area = MIN_AREA
for cnt in contours:
    if cv2.contourArea(cnt) > area:
        area = cv2.contourArea(cnt)
        cnt_length = cv2.arcLength(cnt, True)
        approx = cv2.approxPolyDP(cnt, 0.02*cnt_length, True)
        vtx = len(approx)
        if vtx >= 4:
            (x, y, w, h) = cv2.boundingRect(cnt)
            ratio = w/h
            if w > MIN_WIDTH and h > MIN_HEIGHT and w < MAX_WIDTH and h < MAX_HEIGHT and MIN_RATIO < ratio < MAX_RATIO:
                cv2.rectangle(img_copy, (x,y), (x+w,y+h), (0,0,255), 2)
                cv2.rectangle(dst, (x,y), (x+w,y+h), (0,0,255), 2)
                roi = img[y:y+h, x:x+w]
    else:
        continue

cv2.imshow('img', img_copy)
cv2.imshow('dst', dst)
cv2.imshow('roi', roi)
cv2.imwrite(file_path+'_roi.jpg', roi)

################################ 번호판 글자 추출 ################################
# text = pytesseract.image_to_string(roi, lang='Hangul')
# text = re.compile('[^가-힣|a-z|A-Z|0-9]').sub('', text)
# if text.isspace() or text == None:
#     print('검출된 번호판이 없습니다.')
# else:   print(text)

api_url = 'https://lgvp44vfs2.apigw.ntruss.com/custom/v1/26724/595067f76da9fea01386f8b237b39e29374a31624b6c993101a1f614ef51dc9b/general'
secret_key = 'Z2JnVm1uWnhoUVF0cXRqQlBWRmlUSWdiQ2JDWUFUdkw='

request_json = {'images': [{'format': 'jpg',
                                'name': 'demo'
                               }],
                    'requestId': str(uuid.uuid4()),
                    'version': 'V2',
                    'timestamp': int(round(time.time() * 1000))
                   }

path = file_path+'_roi.jpg'
files = [('file', open(path,'rb'))]
payload = {'message': json.dumps(request_json).encode('UTF-8')}
headers = {'X-OCR-SECRET': secret_key,} 
response = requests.request("POST", api_url, headers=headers, data=payload, files=files)
result = response.json()

car_num = []
for field in result['images'][0]['fields']:
    text = field['inferText']
    text = re.compile('[^가-힣|0-9]').sub('', text)
    car_num.append(text)

print(''.join(car_num))

cv2.waitKey(0)
cv2.destroyAllWindows()