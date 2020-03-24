library(ggplot2)
library(RColorBrewer)
whole <- read.csv("C:/R/lotto.csv")

# real: 실제 로또 데이터, ex: Excel, py: Python, r: R
real <- whole$real; ex <- whole$ex; py <- whole$py; r <- whole$r

# fre: Frequency
fre_real <- table(real); fre_ex <- table(ex); fre_py <- table(py); fre_r <- table(r)
par(mfrow=c(1,1)) # 그래프 출력 한번에

# Compre real with Excel, Python or R
plot(fre_real, type="p", col="red",
     xlab = "real & Excel", ylab = "frequency",
     ylim = c(40, 90))+
  lines(fre_real, type="l", col="red")
par(new=T)
lines(fre_ex, type="p", col="purple")+
  lines(fre_ex, type="l", col="purple")

plot(fre_real, type="p", col="red",
     xlab = "real & Python", ylab = "frequency",
     ylim = c(40, 90))+
  lines(fre_real, type="l", col="red")
par(new=T)
lines(fre_py, type="p", col="skyblue")+
  lines(fre_py, type="l", col="skyblue")

plot(fre_real, type="p", col="red",
     xlab = "real & R", ylab = "frequency",
     ylim = c(40, 90))+
  lines(fre_real, type="l", col="red")
par(new=T)
lines(fre_r, type="p", col="green")+
  lines(fre_r, type="l", col="green")

# 4개 데이터 한번에 
plot(fre_ex, type="p", col="purple",
     xlab = "Excel, Python & R",
     ylab = "frequency",
     ylim = c(40, 90))+
  lines(fre_ex, type="l", col="purple")
par(new=T)
lines(fre_py, type="p", col="skyblue")+
  lines(fre_py, type="l", col="skyblue")
par(new=T)
lines(fre_r, type="p", col="green")+
  lines(fre_r, type="l", col="green")
par(new=T)
lines(fre_real, type="p", col="red")+
  lines(fre_real, type="l", col="red")

# random 수 중 최소값, 최대값 
min(fre_r); max(fre_r)

par(mfrow=c(1,1))
# lotto number Sorting 
barplot(sort(fre_real, decreasing = T), las=2, col=brewer.pal(n = 45, name = "YlOrRd"), xlab="real")
barplot(sort(fre_ex, decreasing = T), las=2, col=brewer.pal(n = 45, name = "BuPu"), xlab="Excel")
barplot(sort(fre_py, decreasing = T), las=2, col=brewer.pal(n = 45, name = "Blues"), xlab="Python")
barplot(sort(fre_r, decreasing = T), las=2, col=brewer.pal(n = 45, name = "BrBG"), xlab="R")
