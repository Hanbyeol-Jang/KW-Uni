df1 <- read.csv("mer_gi6.csv")
head(df1)

df1$car <- scale(df1$car)
head(df1)
write.csv(df1, file="gi_test2.csv")
