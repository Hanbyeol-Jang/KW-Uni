import urllib.request
import urllib.parse
from bs4 import BeautifulSoup

defaultURL= 'http://opernapi.naver.com/search/kin.xml?'
sort = '&sort=sim'
start = '&start=1'
display = '&display=100'
query = '&query='+urllib.parse.quote_plus(str(input("검색어 입력: ")))
fullURL = defaultURL + sort + start + display + query

print(fullURL)

file = open("C:\\Python36\\naver_news3.txt","w",encoding='utf-8')

headers={
    'Host':'openapi.naver.com',
    'User-Agent':'cur1/7.43.0',
    'Accept':'*/*',
    'Content-Type':'application/xml',
    'X-Naver-Client-Id':'UahBuix1_tgp_cvlRO0_',
    'X-Naver-Client-Secret':'c5z_BtP0HU'
    }
req=urllib.request.Request(fullURL, headers=headers)
f=urllib.request.urlopen(req)
resultXML=f.read()

xmlsoup=BeautifulSoup(resultXML,'html.parser')
items=xmlsoup.find_all('item')

for item in items:
    file.write("----------------------------------------\n")
    file.write("블로그 제목: "+ item.title.get_text(strip=True) + '\n')
    file.write("요약  내용: "+ item.description.get_text(strip=True)+ '\n')
    file.write('\n')

file.close()
