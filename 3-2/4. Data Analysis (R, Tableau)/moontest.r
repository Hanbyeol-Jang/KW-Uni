library(KoNLP)
library(dplyr)
library(rJava)
library(stringr)
library(wordcloud)
library(RColorBrewer)

txt<-readLines("C:/MOON.txt")
head(txt)
# 특수문제 제거 
txt <- str_replace_all(txt, "\\W", " ")
# 가사에서 명사 추출 
nouns <- extractNoun(txt)
# 추출한 명사 list를 문자열 벡터로 변환, 단어별 빈도표 생성 
wordcount <- table(unlist(nouns))
# 데이터 프레임으로 변환 
df_word <- as.data.frame(wordcount, stringsAsFactors = F)
# 변수명 수정 
df_word <- rename(df_word,
                  word = Var1,
                  freq = Freq)
# 두 글자 이상 단어 추출 
df_word <- filter(df_word, nchar(word) >= 2)
top_20 <- df_word %>%
  arrange(desc(freq)) %>%
  head(20)
top_20

pal <- brewer.pal(9, "Blues")[5:9] # 색상 목록 생성 
set.seed(1234)                     # 난수 고정

wordcloud(words = df_word$word,    # 단어
          freq = df_word$freq,     # 빈도
          min.freq = 1,            # 최소 단어 빈도
          max.words = 200,         # 표현 단어 수
          random.order = F,        # 고빈도 단어 중앙 배치
          rot.per = .1,            # 회전 단어 비율
          scale = c(4, 0.3),       # 단어 크기 범위
          colors = pal)            # 색상 목록 
