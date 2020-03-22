x <- c(16, 7, 2, 6, 4, 1, 7, 1, 1, 1,
       3, 2, 11, 1, 5, 1, 4, 12)
mean(x)
median(x)
names(which.max(table(x)))
par(mfrow=c(1,1))
hist(x)
hist(x, probability = T)
boxplot(x, horizontal =T)
