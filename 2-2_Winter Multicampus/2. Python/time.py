def cal_time(time):
    if time<24*60*60:
        hour = time//(60*60)
        time = time - hour*60*60
        
        minute = time//60
        time = time - minute*60
        second = time
        print("%d 시 %d 분 %d 초 입니다." %(hour,minute,second))
    else:
        print("입력 시간이 하루를 초과합니다.")
        
time=int(input("초 입력: "))
cal_time(time)
