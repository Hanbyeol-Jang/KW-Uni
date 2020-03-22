import random

computer_number = random.randint(1,100)

def is_same(target, number):
    if target == number:
        result='win'
    elif target > number:
        result='low'
    else:
        result = 'high'
    return result

print("1~100")

guess=int(input("1~100중 하나 입력:"))
horl=is_same(computer_number,guess)

while horl != 'win':
    if horl == 'low':
        guess = int(input("더 큰 숫자 입력: "))
    else:
        guess = int(input("더 작은 숫자 입력: "))
    horl = is_same(computer_number, guess)

input("정답, 엔터")
