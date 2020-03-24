#install.packages("tictoc")
library(tictoc) # 실행시간 확인할 수 있는 라이브러리 추가

cat("[Insertion Sort]\n")

# Insertion Sort 함수 정의 부분
InsertionSort <- function(array)
{
  n <- length(array) # 정렬 하고자 하는 배열의 길이 저장
  i <- 2; j <- 1     # 변수 초기화 
  key <- 0
  while(1)
  {
    key = array[i] # key 값 변경
    j = i -1       # 위치 변경 
  
   while ((j > 0) && array[j] > key)  # Insertion 위치 찾는 부분 
   {                                # key 보다 작은 값을 찾으면 loop 중단 
     array[j + 1] = array[j];       # 배열 한 칸씩 옮겨가며 찾음 
     j = j - 1;       
   }
   
   array[j+1] = key;        # 실제 Insertion
   cat(i-1, ":      ")      # 몇 번째 연산인지 출력 
   cat(array,"\n")
   
   i = i + 1            # 다음 배열 element 로 옮김 
   
   if(i == n + 1)      # 배열의 길이 + 1 은 끝까지 다 갔다는 뜻 
     break
  }
  array       # sort 된 배열 반환  
}
############################################################

array1 <- c(8:1)      # 1~8 역순 정렬 
array2 <- c(16:1)     # 1~16
array3 <- c(32:1)     # 1~32

array4 <- c(128:1)    # 1~128
array5 <- c(256:1)    # 1~256

n1 <- length(array1)

tic("sleeping")       # 실행 시작 시간 
array1 <- InsertionSort(array1) # Insertion Sort 함수 호출 
cat("Output: ", array1, "\n")
timeinfo<-toc()       # 실행 끝나는 시간 
RT1 <- timeinfo$toc - timeinfo$tic # 끝나는 시간 - 시작 시간 = 실행시간 ;
RT1
plot(n1, RT1, type="o",                   # x 축 : n의 갯수, y축 : 실행 시간 
     col="red", cex=2,                    # 그래프 색 및 두께 설정 
     xlim = c(4,256), ylim = c(0,26),     # x축, y축 범위 설정 
     xlab ="n", ylab="Running Time(s)") 

n2 <- length(array2)

tic("sleeping")
array2 <- InsertionSort(array2)
cat("Output: ", array2, "\n")
timeinfo<-toc()
RT2 <- timeinfo$toc - timeinfo$tic
RT2
points(n2, RT2, col="red", cex=2)              # 점 추가
lines(c(n1,n2),c(RT1,RT2), col="red", cex=2)   # 선 추가 

n3 <- length(array3)

tic("sleeping")
array3 <- InsertionSort(array3)
cat("Output: ", array3, "\n")
timeinfo<-toc()
RT3 <- timeinfo$toc - timeinfo$tic
RT3
points(n3, RT3, col="red", cex=2)
lines(c(n2,n3),c(RT2,RT3), col="red", cex=2)

n4 <- length(array4)

tic("sleeping")
array4 <- InsertionSort(array4)
cat("Output: ", array4, "\n")
timeinfo<-toc()
RT4 <- timeinfo$toc - timeinfo$tic
RT4
points(n4, RT4, col="red", cex=2)
lines(c(n3,n4),c(RT3,RT4), col="red", cex=2)

n5 <- length(array5)

tic("sleeping")
array5 <- InsertionSort(array5)
cat("Output: ", array5, "\n")
timeinfo<-toc()
RT5 <- timeinfo$toc - timeinfo$tic
RT5
points(n5, RT5, col="red", cex=2)
lines(c(n4,n5),c(RT4,RT5), col="red", cex=2)
