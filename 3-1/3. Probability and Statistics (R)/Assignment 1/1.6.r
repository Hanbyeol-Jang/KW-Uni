x <- c(1, 2, 1, 0, 2, 2, 1, 1, 0, 0,
       2, 2, 1, 1, 0, 0, 1, 2, 1, 1)
par(mfrow = c(1,2))
hist(x)
hist(x, probability = T)
