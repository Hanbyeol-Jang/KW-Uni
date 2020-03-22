par(mfrow=c(1,3))

plot(dhyper(x=c(0:20), 10, 40, 10), type="h", xlim = c(0,20), ylim = c(0,0.4),
     main="HG(50,10,10)", xlab= "x",ylab=" ",lwd=2,col=2)
plot(dhyper(x=c(0:20), 25, 25, 10), type="h", xlim = c(0,20), ylim = c(0,0.4),
     main="HG(50,25,10)", xlab= "x",ylab=" ",lwd=2,col=3)
plot(dhyper(x=c(0:20), 40, 10, 10), type="h", xlim = c(0,20), ylim = c(0,0.4),
     main="HG(50,40,10)", xlab= "x",ylab=" ",lwd=2,col=4)
