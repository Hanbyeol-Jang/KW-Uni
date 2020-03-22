x <- 0:20

par(mfrow=c(1,2))
plot(x,dbinom(x,20,0.1), type="l",col="2",lwd=2,ylim=c(0,0.4),ylab="")
lines(x,dbinom(x,20,0.3),col="3",lwd=2)
lines(x,dbinom(x,20,0.5),col="4",lwd=2)
lines(x,dbinom(x,20,0.7),col="5",lwd=2)
lines(x,dbinom(x,20,0.9),col="6",lwd=2)
legend(legend=c("B(20,0.1)","B(20,0.3)","B(20,0.5)","B(20,0.7)","B(20,0.9)"),
       fill=2:6,x=7,y=0.375)

plot(x,dbinom(x,20,0.1), type="l",col="2",lwd=2,ylim=c(0,0.4),ylab="",lty=1)
lines(x,dbinom(x,20,0.3),col="3",lwd=2,lty=2)
lines(x,dbinom(x,20,0.5),col="4",lwd=2,lty=3)
lines(x,dbinom(x,20,0.7),col="5",lwd=2,lty=4)
lines(x,dbinom(x,20,0.9),col="6",lwd=2,lty=5)
legend(legend=c("B(20,0.1)","B(20,0.3)","B(20,0.5)","B(20,0.7)","B(20,0.9)"),lty=1:5,
       x=7,y=0.375,col=2:6,lwd=2)
