library(ggplot2)
library(RColorBrewer)
whole <- read.csv("C:/R/lotto.csv")

real <- whole$real; ex <- whole$ex; py <- whole$py; r <- whole$r
fre_real <- table(real); fre_ex <- table(ex); fre_py <- table(py); fre_r <- table(r)
par(mfrow=c(2,2))

barplot(sort(fre_real, decreasing = T), las=2, col=brewer.pal(n = 45, name = "YlOrRd"), xlab="real")
barplot(sort(fre_ex, decreasing = T), las=2, col=brewer.pal(n = 45, name = "BuPu"), xlab="Excel")
barplot(sort(fre_py, decreasing = T), las=2, col=brewer.pal(n = 45, name = "Blues"), xlab="Python")
barplot(sort(fre_r, decreasing = T), las=2, col=brewer.pal(n = 45, name = "BrBG"), xlab="R")
