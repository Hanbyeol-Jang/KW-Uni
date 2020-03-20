df1 <- read.csv("merged_data1.csv", TRUE, fileEncoding = 'utf-8')
df2 <- read.csv("date6.csv")

df3 <- merge(df2, df1, by='date')
head(df1)
head(df2)
head(df3)

df3$pop <- scale(df3$pop)
df3$soq <- scale(df3$soq)
df3$car <- scale(df3$car)
  
head(df3)
write.csv(df3, file="mer_gi8.csv")
