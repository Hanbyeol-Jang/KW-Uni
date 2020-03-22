x <- c(61, 93, 91, 86, 55, 63, 86, 82, 76, 57,
       94, 89, 67, 62, 72, 87, 68, 65, 75, 84)
stem(x)
stem(x, scale = 2)
stem(x, scale = 0.5)
quantile(x, type=6)
IQR(x, type=6)
boxplot(x, type=6, horizontal = T)
