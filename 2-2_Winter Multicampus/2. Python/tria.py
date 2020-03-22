h = float(input("높이를 입력하세요(m): "))
num=0

while h>=0.00001:
    h=h/2
    num+=1

print("공이 튀긴 횟수는 %d" %(num-1))
