library(ggplot2)
library(RColorBrewer)
whole <- read.csv("C:/R/lotto.csv")

# real: 실제 로또 데이터, ex: Excel, py: Python, r: R
real <- whole$real; ex <- whole$ex; py <- whole$py; r <- whole$r

# fre: Frequency
fre_real <- table(real); fre_ex <- table(ex); fre_py <- table(py); fre_r <- table(r)

pie(sort(fre_real,decreasing = T), col=brewer.pal(n = 45, name = "YlOrRd"))
pie(sort(fre_ex,decreasing = T), col=brewer.pal(n = 45, name = "BuPu"))
pie(sort(fre_py,decreasing = T), col=brewer.pal(n = 45, name = "Blues"))
pie(sort(fre_r,decreasing = T), col=brewer.pal(n = 45, name = "BrBG"))

