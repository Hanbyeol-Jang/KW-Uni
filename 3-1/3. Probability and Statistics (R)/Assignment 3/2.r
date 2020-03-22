a=c(); b=c(); c=c(); d=c();

for(i in 1:5000)
{
  a[i] = mean(sample(1:10, 1, replace = T))
  b[i] = mean(sample(1:10, 20, replace = T))
  c[i] = mean(sample(1:10, 50, replace = T))
  d[i] = mean(sample(1:10, 100, replace = T))
}

par(mfrow=c(1,4))
hist(a, prob=T, xlim=c(1,10), xlab="n=1")
hist(b, prob=T, xlim=c(1,10), xlab="n=10", breaks=30)
hist(c, prob=T, xlim=c(1,10), xlab="n=30", breaks=30)
hist(d, prob=T, xlim=c(1,10), xlab="n=100", breaks=30)
