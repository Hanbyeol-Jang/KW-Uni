df1 <- read.csv("mer_gi7.csv")
head(df1)

df1$pop <- scale(df1$pop)
df1$soq <- scale(df1$soq)
df1$car <- scale(df1$car)
head(df1)
write.csv(df1, file="gi_test1.csv")
