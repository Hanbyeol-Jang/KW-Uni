a=c(); b=c(); c=c(); d=c();

for(i in 1:5000)
{
  a[i] = mean(rnorm(1,0,1))
  b[i] = mean(rnorm(2,0,1))
  c[i] = mean(rnorm(4,0,1))
  d[i] = mean(rnorm(8,0,1))
}

par(mfrow=c(1,4))
hist(a, prob=T, xlim=c(-3,3), xlab="n=1")
hist(b, prob=T, xlim=c(-3,3), xlab="n=2", breaks=30)
hist(c, prob=T, xlim=c(-3,3), xlab="n=4", breaks=30)
hist(d, prob=T, xlim=c(-3,3), xlab="n=8", breaks=30)
