n1 = int(input("첫 번째 정수 입력: "))
n2 = int(input("두 번째 정수 입력: "))
n3 = int(input("세 번째 정수 입력: "))
summ= n1+n2+n3
Max=0

if summ%2==0:
    if n1 >= n2:
        Max = n1
    else:
        Max = n2
    
    if Max >= n3:
        print(Max)
    else:
        print(n3)
else:
    print(summ)
    
