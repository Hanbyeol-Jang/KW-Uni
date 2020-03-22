def highscore(aa):
    Max=[]
    aa=[]
    for j in range(0,6):
        if aa[j]>=aa[j+3]:
            Max[j]=aa[j]
        elif aa[j]<aa[j+3]:
            Max[j]=aa[j+3]
    print(Max)

score=[]

for i in range(0,6):
    num=int(input("%d 번째 학생 시험 점수 입력: " %(i+1)))
    score.append(num)

highscore(score)


