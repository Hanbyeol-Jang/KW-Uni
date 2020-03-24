library(ggplot2)
library(RColorBrewer)
real <- read.csv("C:/R/real_sort.csv")
fre<-table(real)

barplot(sort(fre, decreasing = T), las=2, col=brewer.pal(n = 45, name = "YlOrRd"))
