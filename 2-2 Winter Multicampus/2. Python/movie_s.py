import os
import urllib.parse
import urllib.request
import re
import time
import random

from bs4 import BeautifulSoup

url1='http://movie.naver.com/movie/bi/mi/pointWriteFormList.nhn?code='
url2='&type=after&isActualPointWriteExecute=false&MileageSubscriptionReject=false&page='

hdr={
    'User-Agent':'Mozilla/5.0(Windows NT 6.3;WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/46.0.2490.86 Safari/537.36',
    'Host':'movie.naver.com',
    'Connection':'keep-alive',
    'referer':'http://m.naver.com'
    }

def split_url():
    url=input('url을 입력하세요: ')
    code_str=re.search('code=[0-9]*',url).group()
    code=re.search('[0-9]+', code_str).group()

    return code

def fetch_score_result(URL):
    print(URL)
    result={}
    result_list=[]

    res=urllib.request.Request(URL, headers=hdr)
    response=urllib.request.urlopen(res)

    html = response.read()

    soup = BeautifulSoup(html, 'html.parser')

    score_result = soup.find('div', class_='score_result').find('ul')
    lis = score_result.find_all('li')

    for li in lis:
        score = li.find('div', class_='star_score').find('em').get_text()

        spectator = li.find('div', class_='score_reple').find('span').get_text()
        review=li.find('div', class_='score_reple').find('p').get_text()

        if spectator == '관람객':
            review = review[3:]

        result['score'] = score
        result['review'] = review

        result_list.append({
            'score' : score,
            'review' : review
            })

    return result_list

def input_save_path():
    save_path = str(input("input save path: "))
    save_path = save_path.replace('\\', '/')
    if not os.path.isdir(os.path.split(save_path)[0]):
        os.mkdir(os.path.split(save_path)[0])
    return save_path

def fetch_reviews():
    code = split_url()
    f=open(input_save_path(), 'w', encoding='utf-8')
    page =1
    
    while True:
        count = int(input("게시물의 검색 개수 입력(10단위): "))
        if count%10 ==0:
            break
    l_count=1
    isLoop = True

    while isLoop:
        URL = url1 + code + url2 + str(page)
        result_list = fetch_score_result(URL)

        for r in result_list:
            f.write('=='*40+'\n')
            f.write('영화 평점: ' +r['score'] + '\n')
            f.write('리뷰 내용: ' +r['review'] + '\n')
            f.write('==' *40 + '\n')
            l_count+=1
            if l_count > count:
                isLoop = False
                break

        page +=1

        if not isLoop or l_count == count:
            isLoop = False
            break

        sleepTime = random.randint(4, 10)
        time.sleep(sleepTime)
        print(str(sleepTime) + '초 기다렸습니다.')
    f.close()
    
fetch_reviews()


        
