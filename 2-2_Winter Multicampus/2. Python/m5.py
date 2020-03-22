def list_avg(numlist):
    summ=0
    avg=0
    for i in range(0, len(numlist)):
        summ+=numlist[i]
    avg=summ/len(numlist)

    return avg

math_score=[90,80,70,50,60]
print(list_avg(math_score))
