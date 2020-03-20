df1 <- read.csv("merged_test1.csv", TRUE, fileEncoding = 'utf-8')
df2 <- read.csv("date6.csv")

head(df1)
df3 <- merge(df2, df1, by='date')
head(df3)

df3$pop <- scale(df3$pop, center = TRUE)
df3$soq <- scale(df3$soq, center = TRUE)
df3$car <- scale(df3$car, center = TRUE)

scale(x, center = TRUE, scale = TRUE)

head(df3)
write.csv(df3, file="merged_test2.csv")
