x<-0:20
par(new=T)
plot(x-0.1,dhyper(x,50,950,20),type="h",xlim=c(0,10),ylim=c(0,0.7),
     col=2, lwd=2, xlab=" ", ylab=" ")
lines(x+0.1,dbinom(x, 20, 0.05), type="h",xlim=c(0,10),ylim=c(0,0.7),
          col=4, lwd=2, xlab=" ", ylab=" ")
legend("top",legend=c("HG(1000,50,20)","B(20,0.05)"),
       fill=c(2,4),x=6, y=0.6)
