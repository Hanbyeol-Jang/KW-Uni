# udate는 시분초까지 필요
# ucdate는 날짜만 있으면 됨
# text를 저장안함
install.packages("ROAuth")
library(ROAuth)
load("my_oauth")

install.packages("twitteR")
install.packages("streamR")
library(xlsx)
library(twitteR)
library(streamR)
library(plyr)

parsj <- function(fn)
{vnames <-c("id_str","text","source","lang")
tmp <- parseTweets(fn)[,vnames]
tmp$source <- substr(tmp$source, 1, nchar(tmp$source)-4)
tmp$source <- sub('.*\\">', "", tmp$source)
tmp
}

head(fn)
a=parseTweets(fn)
head(a)
dimnames(a)

fn <- paste("C:/Users/bigdataku/Desktop/testjson/",fns,"",sep="")
tmp <- parsj(fn)
head(tmp$text)
tmp[,1]=str_replace_all(tmp[,1],"[[\r\n]]", "")

df=data.frame(tmp)
head(df)
head(df$text)

getOption("encoding")
Encoding(tmp$text) <- "UTF-16"
Encoding(tmp$source) <- "UTF-8"
unique(tmp$source)

write.table(tmp$text,"test.txt",row.names=F,col.names=F,quote=F)
write.table(tmp$text,"test.txt",row.names=F,col.names=F,quote=F)


write.csv(tmp$text,"C:/Users/bigdataku/Desktop/testjson/test.csv",row.names=F)
write.table(tmp$text,"C:/Users/bigdataku/Desktop/testjson/test.txt",row.names=F,quote=F)

write.table(tmp$text,"test.txt",row.names=F,col.names=F,quote=F)
getwd()

install.packages("readr")
library(readr)

for (i in 1:length(fns)){
  fn <- paste("C:/Users/bigdataku/Desktop/testjson/",fns[i],"",sep="")
  cat("Parsing ", fn, "\n")
  tmp <- parsj(fn)
  tmp[,1]=str_replace_all(tmp[,1],"[[\r\n]]", "")
  fncsv <- paste("C:/Users/bigdataku/Desktop/texts/",fns[i],".csv",sep="")
  cat("    Writing ", fncsv,"\n")
  write.csv(tmp,file=fncsv,row.names=F)
}
write_csv(tmp,fncsv)
write.csv(tmp,file=fncsv,row.names=F)
Encoding(tmp$text)<-"latin1"
write.csv(tmp,file=fncsv,row.names=F)
tmp
con=file("fncsv",encoding="utf8")
write.csv(tmp,file=fncsv)

tmp
head(tmp$text)
write.csv(tmp$text,file=fncsv)
write.csv(tmp,file=fncsv)
Encoding(tmp$text) <- "latin1"

tmp$text <- iconv(tmp$text, "latin1", "UTF-8",sub='')
head(tmp$text)

head(tmp)
tmp1=str_replace_all(tmp,"[[\r\n]]", "")
head(tmp1)

  tmp1=str_replace_all(df[,1],"[[:punct:],[\r\n]]", "")
  tmp2=str_replace_all(df[,2],"[[:punct:]]", "")
  df1=iconv(tmp1, "latin1", "ASCII", sub="")
  df2=iconv(tmp2, "latin1", "ASCII", sub="")

head(tmp$text)
str<-tmp$text[6]
Encoding(str)
write.table(str, file=fncsv, quote=F, col.names=F, row.names=F,stringsAsFactors=FALSE)

iconv(str, from = "UTF-8")
bb=data.frame(str,str)
bb[1]

kor=sqldf('select text from tmp where lang="ko"')
length(kor)
dim(kor)
tail(tmp$text)
dim(tmp)
Encoding(tmp[4384,1])<-"UTF-8"
tmp[4384,1]
Encoding(tmp$text)<-"UTF-8"
head(tmp$text)
write.csv(tmp$text,file=fncsv)
library(textcat)
textcat(tmp[6,1])
textcat(tmp[1,1])
textcat(tmp[2,1])
textcat(tmp[3,1])
textcat(tmp[4,1])

head(tmp$text)
tmp[6,1]
install.packages("textcat")
textcat(kor[2,1])
kor[1,1]
Encoding(kor[1,1]) <- "UTF-8"
Encoding(kor[2,1]) <- "UTF-8"
kor[1,1]
kor[2,1]
kor
iconv(kor)
Encoding(kor)
write.table(kor,fncsv,fileEncoding="UTF-8")
Encoding(kor[,])
kor
str=tmp$text
Encoding(str) <- "UTF-8"
Encoding(str[1]) <- "UTF-8"
head(Encoding(str))
head(str)

tmp[4376,1]
tmp$text[4376]
enc2utf8(as(tmp$text, "character"))
iconv(kor,to="ASCII//TRANSLIT")

library(stringi)
tail(stri_enc_mark(tmp$text))
tail(tmp$text)
all(stri_enc_isutf8(tmp$text))
tmp$text <- stri_encode(tmp$text, "", "UTF-8")
stri_trans_general(tmp$text, "Latin-ASCII")
tail(Encoding(tmp$text))
#######################################################

cname <- "C:/Users/bigdataku/Desktop/texts/"
cname
dir(cname)   
docs <- Corpus(DirSource(cname))   
docs
summary(docs)

docs <- tm_map(docs, removePunctuation)
inspect(docs[1])
docs[1]

for(j in seq(docs))   
   {   
     docs[[j]] <- gsub("/", " ", docs[[j]])   
     docs[[j]] <- gsub("@", " ", docs[[j]])   
     docs[[j]] <- gsub("\\|", " ", docs[[j]])   
  } 
docs <- tm_map(docs, removeNumbers)
dim(docs)
docs[1]

inspect(docs[1])
inspect(docs[2])
inspect(docs[3])
docs <- tm_map(docs, tolower)
inspect(docs[1])
docs <- tm_map(docs, removeWords, stopwords("english"))
inspect(docs[1])
inspect(docs[2])
inspect(docs[3])

for (j in seq(docs))
{
docs[[j]] <- gsub("qualitative research", "QDA", docs[[j]])
docs[[j]] <- gsub("qualitative studies", "QDA", docs[[j]])
docs[[j]] <- gsub("qualitative analysis", "QDA", docs[[j]])
docs[[j]] <- gsub("research methods", "research_methods", docs[[j]])
}
inspect(docs[1])
inspect(docs[2])
inspect(docs[3])

library(SnowballC)   
docs <- tm_map(docs, stemDocument)  
inspect(docs[1])
docs <- tm_map(docs, stripWhitespace)
inspect(docs[1])
docs <- tm_map(docs, PlainTextDocument)
inspect(docs[1])
inspect(docs[2])
inspect(docs[3])
docs

dtm <- DocumentTermMatrix(docs)   
dtm
inspect(dtm)

tdm <- TermDocumentMatrix(docs)   
tdm   

freq <- colSums(as.matrix(dtm))   
length(freq)  

ord <- order(freq)

dtms <- removeSparseTerms(dtm, 0.1) # This makes a matrix that is 10% empty space, maximum.   
inspect(dtms) 

freq[head(ord)] 
freq[tail(ord)]   
head(table(freq), 20)  

freq <- colSums(as.matrix(dtms))   
freq   

freq <- sort(colSums(as.matrix(dtm)), decreasing=TRUE)
freq
head(freq, 14)   

findFreqTerms(dtm, lowfreq=50)

wf <- data.frame(word=names(freq), freq=freq)   
head(wf)  

library(ggplot2)   
p <- ggplot(subset(wf, freq>50), aes(word, freq))    
p <- p + geom_bar(stat="identity")   
p <- p + theme(axis.text.x=element_text(angle=45, hjust=1))   
p   

library(wordcloud)
set.seed(142)   
wordcloud(names(freq), freq, min.freq=100)  

dtmss <- removeSparseTerms(dtm, 0.15) # This makes a matrix that is only 15% empty space, maximum.   
inspect(dtmss)   

library(cluster)   
d <- dist(t(dtmss), method="euclidian")   
fit <- hclust(d=d, method="ward")   
fit   

plot(fit, hang=-1)   

plot.new()
plot(fit, hang=-1)
groups <- cutree(fit, k=5)   # "k=" defines the number of clusters you are using   
rect.hclust(fit, k=5, border="red") # draw dendogram with red borders around the 5 clusters  


library(fpc)   
d <- dist(t(dtmss), method="euclidian")   
kfit <- kmeans(d, 2)   
clusplot(as.matrix(d), kfit$cluster, color=T, shade=T, labels=2, lines=0)   