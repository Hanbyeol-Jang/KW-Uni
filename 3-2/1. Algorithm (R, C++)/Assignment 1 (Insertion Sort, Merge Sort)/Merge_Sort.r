library(tictoc) # ����ð� Ȯ���� �� �ִ� ���̺귯�� �߰�

cat("[Merge Sort]\n")

# Merge Sort �Լ� ���� �κ� 
MergeSort <- function(array)
{
  n <- length(array) # ���� �ϰ��� �ϴ� �迭�� ũ�� ����
  if (n < 2)         # n �� �� �ϳ� �ۿ� ���� �� ����
    return(array)    # Ȥ�� Divide �� ��������� �����Ͽ�  1�� �� �ɶ� ���� 
  
  cat("[Divide] ")
  first <- array[1:(n %/% 2)]    # �迭�� �������� ���� �� �κ��� first �� ���� 
  cat(first, " | ")              # | �� �� �� ���� 
  last <- array[(n %/% 2 + 1):n] # �� �κ��� last �� ���� 
  cat(last, " ")
  cat("\n")

  first <- MergeSort(first)    # ��������� �����Ͽ�
  last <- MergeSort(last)      # divide�� ���̻� ���� �Ҽ� ���� �� ����
  
  temp <- c()         # ���� �ʱ�ȭ 
  i <- 0
  
  while(length(first) > 0 && length(last) > 0) # �� �� �迭�� ���̰� �ϳ��� ���� ������ ��� ���� 
  {
    if(first[1] < last[1])          # �չ迭�� ù ��° ���� �޹迭�� ù ��° ������ ���� �� 
    {
      temp[i + 1] <- first[1]       # �չ迭�� ù ��° �� ����
      first <- first[-1]            # �չ迭�� ù ��° �� ����
    }
    else                            # �޹迭�� ù ��° ���� ������ 
    {
      temp[i + 1] <- last[1]        # �޹迭�� ù ��° �� ���� 
      last <- last[-1]              # �޹迭�� ù ��° �� ���� 
    }
    i = i + 1                       # �迭�� ���� ������ �̵� 
  }
  temp <- c(temp, first, last)      # ������ �迭�� �� �ֱ�
  cat("[Conquer] ")
  cat(temp, "\n")                   # �������� �迭 ��� �� 
  temp                              # ��ȯ 
}
############################################################

array1 <- c(8:1)      # 1~8 ���� ���� 
array2 <- c(16:1)     # 1~16
array3 <- c(32:1)     # 1~32
array4 <- c(128:1)    # 1~128
array5 <- c(256:1)    # 1~256

n1 <- length(array1)

tic("sleeping")       # ���� ���� �ð� 
array1 <- MergeSort(array1)
cat("Output: ", array1, "\n")
timeinfo<-toc()       # ���� ������ �ð� 
RT1 <- timeinfo$toc - timeinfo$tic # ������ �ð� - ���� �ð� = ����ð� ;
RT1
points(n1, RT1, type="o",                   # x �� : n�� ����, y�� : ���� �ð� 
     col="blue", cex=2,                    # �׷��� �� �� �β� ���� 
     xlim = c(4,256), ylim = c(0,26),     # x��, y�� ���� ���� 
     xlab ="n", ylab="Running Time(s)") 

n2 <- length(array2)

tic("sleeping")
array2 <- MergeSort(array2)
cat("Output: ", array2, "\n")
timeinfo<-toc()
RT2 <- timeinfo$toc - timeinfo$tic
RT2
points(n2, RT2, col="blue", cex=2)              # �� �߰�
lines(c(n1,n2),c(RT1,RT2), col="blue", cex=2)   # �� �߰� 

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
