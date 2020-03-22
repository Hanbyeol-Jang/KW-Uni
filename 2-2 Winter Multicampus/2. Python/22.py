import urllib.request
import urllib.parse

from bs4 import BeautifulSoup

defaultURL= 'http://opernapi.naver.com/search?&'
key = 'key=이곳에 독자님의 Open API 키를 입력하세요'
target = '&target=blog' #naver blog를 검색하는 부분
sort = '&sort=sim'
start = '&start=1'
display = '&display=100'
query = '&query='+urllib.parse.quote_plus(str(input("검색어 입력: ")))
fullURL = defaultURL + key + target + sort + start + display + query

print(fullURL)

file = open("C:\\Python36\\naver_blog.txt","w",encoding='utf-8')
f=urllib.request.urlopen(fullURL)
resultXML=f.read()

xmlsoup=BeautifulSoup(resultXML,'html.parser')
items=xmlsoup.find_all('item')

for item in items:
    file.write("----------------------------------------\n")
    file.write("블로그 제목: "+ item.title.get_text(strip=True) + '\n')
    file.write("요약  내용: "+ item.description.get_text(strip=True)+ '\n')
    file.write('\n')

file.close()
