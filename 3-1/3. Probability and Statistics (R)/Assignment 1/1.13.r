x <- c(87, 109, 79, 80, 96, 95, 90, 92, 96, 98,
       101, 91, 78, 112, 94, 98, 94, 107, 81, 96)
stem(x)
stem(x, scale = 2)
stem(x, scale = 0.5)
quantile(x)
IQR(x)
boxplot(x, horizontal = T)
