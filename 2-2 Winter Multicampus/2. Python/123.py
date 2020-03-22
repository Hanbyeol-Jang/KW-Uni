num=int(input("정수 입력:"))

n5= num//10000
num%=10000
n4= num//1000
num%=1000
n3= num//100
num%=100
n2= num//10
num%=10

ssum=n5+n4+n3+n2+num
print(ssum)

