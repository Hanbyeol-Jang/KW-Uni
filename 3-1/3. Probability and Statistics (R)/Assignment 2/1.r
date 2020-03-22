par(mfrow = c(1,3))

x <- 0:20
plot(x, dbinom(x, 20, 0.1), type = "h")
plot(x, dbinom(x, 20, 0.1), type = "h",
     col = "red", ylim = c(0, 0.3))
plot(x, dbinom(x, 20, 0.1), type = "h",
     col = "red" ,ylim = c(0, 0.3),
     main = "B(20,0.1)", lwd = 2)
