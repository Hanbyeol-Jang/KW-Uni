#install.packages("tictoc")
library(tictoc) # ����ð� Ȯ���� �� �ִ� ���̺귯�� �߰�

cat("[Insertion Sort]\n")

# Insertion Sort �Լ� ���� �κ�
InsertionSort <- function(array)
{
  n <- length(array) # ���� �ϰ��� �ϴ� �迭�� ���� ����
  i <- 2; j <- 1     # ���� �ʱ�ȭ 
  key <- 0
  while(1)
  {
    key = array[i] # key �� ����
    j = i -1       # ��ġ ���� 
  
   while ((j > 0) && array[j] > key)  # Insertion ��ġ ã�� �κ� 
   {                                # key ���� ���� ���� ã���� loop �ߴ� 
     array[j + 1] = array[j];       # �迭 �� ĭ�� �Űܰ��� ã�� 
     j = j - 1;       
   }
   
   array[j+1] = key;        # ���� Insertion
   cat(i-1, ":      ")      # �� ��° �������� ��� 
   cat(array,"\n")
   
   i = i + 1            # ���� �迭 element �� �ű� 
   
   if(i == n + 1)      # �迭�� ���� + 1 �� ������ �� ���ٴ� �� 
     break
  }
  array       # sort �� �迭 ��ȯ  
}
############################################################

array1 <- c(8:1)      # 1~8 ���� ���� 
array2 <- c(16:1)     # 1~16
array3 <- c(32:1)     # 1~32

array4 <- c(128:1)    # 1~128
array5 <- c(256:1)    # 1~256

n1 <- length(array1)

tic("sleeping")       # ���� ���� �ð� 
array1 <- InsertionSort(array1) # Insertion Sort �Լ� ȣ�� 
cat("Output: ", array1, "\n")
timeinfo<-toc()       # ���� ������ �ð� 
RT1 <- timeinfo$toc - timeinfo$tic # ������ �ð� - ���� �ð� = ����ð� ;
RT1
plot(n1, RT1, type="o",                   # x �� : n�� ����, y�� : ���� �ð� 
     col="red", cex=2,                    # �׷��� �� �� �β� ���� 
     xlim = c(4,256), ylim = c(0,26),     # x��, y�� ���� ���� 
     xlab ="n", ylab="Running Time(s)") 

n2 <- length(array2)

tic("sleeping")
array2 <- InsertionSort(array2)
cat("Output: ", array2, "\n")
timeinfo<-toc()
RT2 <- timeinfo$toc - timeinfo$tic
RT2
points(n2, RT2, col="red", cex=2)              # �� �߰�
lines(c(n1,n2),c(RT1,RT2), col="red", cex=2)   # �� �߰� 

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
