library(KoNLP)
library(dplyr)
library(rJava)
library(stringr)
library(wordcloud)
library(RColorBrewer)

txt<-readLines("C:/MOON.txt")
head(txt)
# Ư������ ���� 
txt <- str_replace_all(txt, "\\W", " ")
# ���翡�� ��� ���� 
nouns <- extractNoun(txt)
# ������ ��� list�� ���ڿ� ���ͷ� ��ȯ, �ܾ ��ǥ ���� 
wordcount <- table(unlist(nouns))
# ������ ���������� ��ȯ 
df_word <- as.data.frame(wordcount, stringsAsFactors = F)
# ������ ���� 
df_word <- rename(df_word,
                  word = Var1,
                  freq = Freq)
# �� ���� �̻� �ܾ� ���� 
df_word <- filter(df_word, nchar(word) >= 2)
top_20 <- df_word %>%
  arrange(desc(freq)) %>%
  head(20)
top_20

pal <- brewer.pal(9, "Blues")[5:9] # ���� ��� ���� 
set.seed(1234)                     # ���� ����

wordcloud(words = df_word$word,    # �ܾ�
          freq = df_word$freq,     # ��
          min.freq = 1,            # �ּ� �ܾ� ��
          max.words = 200,         # ǥ�� �ܾ� ��
          random.order = F,        # ��� �ܾ� �߾� ��ġ
          rot.per = .1,            # ȸ�� �ܾ� ����
          scale = c(4, 0.3),       # �ܾ� ũ�� ����
          colors = pal)            # ���� ��� 
