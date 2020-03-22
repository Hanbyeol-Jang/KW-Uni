def highscore(aa):
    Max=0

    if aa[0]>=aa[1]:
        Max=aa[0]
    else:
        Max=aa[1]
    for i in range(2,6):
        if Max >=aa[i]:
           Max=Max
        else:
           Max=aa[i]
           
    return Max
################################################################
    
score=[]

for i in range(0,6):
    num=int(input("%d 번째 학생 시험 점수 입력: " %(i+1)))
    score.append(num)

print("최고점수는 %d " %highscore(score))



