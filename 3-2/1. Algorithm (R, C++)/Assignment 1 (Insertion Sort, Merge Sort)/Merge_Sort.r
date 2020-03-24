library(tictoc) # 실행시간 확인할 수 있는 라이브러리 추가

cat("[Merge Sort]\n")

# Merge Sort 함수 정의 부분 
MergeSort <- function(array)
{
  n <- length(array) # 정렬 하고자 하는 배열의 크기 저장
  if (n < 2)         # n 이 단 하나 밖에 없을 때 종료
    return(array)    # 혹은 Divide 를 계속적으로 수행하여  1개 가 될때 까지 
  
  cat("[Divide] ")
  first <- array[1:(n %/% 2)]    # 배열을 절반으로 나눠 앞 부분을 first 에 저장 
  cat(first, " | ")              # | 로 앞 뒤 구분 
  last <- array[(n %/% 2 + 1):n] # 뒷 부분을 last 에 저장 
  cat(last, " ")
  cat("\n")

  first <- MergeSort(first)    # 재귀적으로 수행하여
  last <- MergeSort(last)      # divide를 더이상 수행 할수 없을 때 까지
  
  temp <- c()         # 변수 초기화 
  i <- 0
  
  while(length(first) > 0 && length(last) > 0) # 앞 뒤 배열의 값이가 하나라도 남아 있으면 계속 실행 
  {
    if(first[1] < last[1])          # 앞배열의 첫 번째 값이 뒷배열의 첫 번째 값보다 작을 때 
    {
      temp[i + 1] <- first[1]       # 앞배열의 첫 번째 값 삽입
      first <- first[-1]            # 앞배열의 첫 번째 값 제거
    }
    else                            # 뒷배열의 첫 번째 값이 작으면 
    {
      temp[i + 1] <- last[1]        # 뒷배열의 첫 번째 값 삽입 
      last <- last[-1]              # 뒷배열의 첫 번째 값 제거 
    }
    i = i + 1                       # 배열의 다음 값으로 이동 
  }
  temp <- c(temp, first, last)      # 정렬할 배열에 다 넣기
  cat("[Conquer] ")
  cat(temp, "\n")                   # 정렬중인 배열 출력 후 
  temp                              # 반환 
}
############################################################

array1 <- c(8:1)      # 1~8 역순 정렬 
array2 <- c(16:1)     # 1~16
array3 <- c(32:1)     # 1~32
array4 <- c(128:1)    # 1~128
array5 <- c(256:1)    # 1~256

n1 <- length(array1)

tic("sleeping")       # 실행 시작 시간 
array1 <- MergeSort(array1)
cat("Output: ", array1, "\n")
timeinfo<-toc()       # 실행 끝나는 시간 
RT1 <- timeinfo$toc - timeinfo$tic # 끝나는 시간 - 시작 시간 = 실행시간 ;
RT1
points(n1, RT1, type="o",                   # x 축 : n의 갯수, y축 : 실행 시간 
     col="blue", cex=2,                    # 그래프 색 및 두께 설정 
     xlim = c(4,256), ylim = c(0,26),     # x축, y축 범위 설정 
     xlab ="n", ylab="Running Time(s)") 

n2 <- length(array2)

tic("sleeping")
array2 <- MergeSort(array2)
cat("Output: ", array2, "\n")
timeinfo<-toc()
RT2 <- timeinfo$toc - timeinfo$tic
RT2
points(n2, RT2, col="blue", cex=2)              # 점 추가
lines(c(n1,n2),c(RT1,RT2), col="blue", cex=2)   # 선 추가 

n3 <- length(array3)

tic("sleeping")
array3 <- MergeSort(array3)
cat("Output: ", array3, "\n")
timeinfo<-toc()
RT3 <- timeinfo$toc - timeinfo$tic
RT3
points(n3, RT3, col="blue", cex=2)
lines(c(n2,n3),c(RT2,RT3), col="blue", cex=2)

n4 <- length(array4)

tic("sleeping")
array4 <- MergeSort(array4)
cat("Output: ", array4, "\n")
timeinfo<-toc()
RT4 <- timeinfo$toc - timeinfo$tic
RT4
points(n4, RT4, col="blue", cex=2)
lines(c(n3,n4),c(RT3,RT4), col="blue", cex=2)

n5 <- length(array5)

tic("sleeping")
array5 <- MergeSort(array5)
cat("Output: ", array5, "\n")
timeinfo<-toc()
RT5 <- timeinfo$toc - timeinfo$tic
RT5
points(n5, RT5, col="blue", cex=2)
lines(c(n4,n5),c(RT4,RT5), col="blue", cex=2)
