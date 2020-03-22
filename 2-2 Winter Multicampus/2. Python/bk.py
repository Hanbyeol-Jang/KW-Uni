import urllib.parse
import urllib.request
import re


def bind_url() :
    default_url = 'http://openapi.naver.com/v1/search/image.xml?'
    start = "&start=1"
    sort ='&sort=sim'
    display = '&display=10'
    query ='&query='+urllib.parse.quote_plus(str(input("검색할 단어 입력")))
    full_url = default_url + sort + start + display + query
    print(full_url)
    return full_url
    
def fetch_contents_from_url() :
    
    url = bind_url()
    
    headers={
        'Host':'openapi.naver.com',
        'User-Agent':'curl/7.43.0',
        'Accept' :'*/*',
        'Content-Type':'application/xml',
        'X-Naver-Client-Id':'pP7OGr9HFzyu98OzWUEy',
        'X-Naver-Client-Secret':'EpygaD4nZS'
        }
    r=urllib.request.Request(url, headers=headers)
    m=urllib.request.urlopen(r)
    print(1)
    html = m.read()
    print(4)
    return html

def extract_text_in_tags(tags,tagname='title') :
    txt =[]
    reg = "[^<"+tagname+">][^<]+"
    for tag in tags :
        txt.append(re.search(reg,tag).group())
    return txt

def get_contents_from_html() :
    html = fetch_contents_from_url()
    title_tags = re.findall("<title>[^<]+</title>",html.decode('utf-8'))
    link_tags = re.findall("<link>[^<]+</link>",html.decode("utf-8"))
    titles = extract_text_in_tags(title_tags,tagname = 'title')
    links = extract_text_in_tags(link_tags,tagname='link')
    f=open("image.html","w")
    f.write("<html><body>")
    for i in range(1,len(titles)):
        f.write("<p>"+title[i]+"</p>")
        f.write("<img src="+links[i]+"/>")
    f.write("</body></html>")
    f.close()

get_contents_from_html()
                               
