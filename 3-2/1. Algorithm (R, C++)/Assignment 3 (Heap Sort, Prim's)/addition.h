#include <iostream>
using namespace std;
#define len 15

void PRINT_TREE(int A[]);		// 배열을 Tree 모양으로 출력하는 함수
int Parent(int i);		// Tree에서 i index인 node 의 parent node의 index를 가져오는 함수
int Left(int i);		// 왼쪽 child 의 index를 가져오는 함수
int Right(int i);		// 오른쪽 child 의 index를 가져오는 함수
void PRINT_ARRAY(int A[]); // 배열의 모든 요소들을 순차적으로 출력하는 함수
int Arrlength(int A[]);		// 배열의 길이를 가져오는 함수

void PRINT_TREE(int A[])
{
	int i = 1;	// 입력된 배열의 첫번째 요소 부터
	while (1)
	{
		if (i == len + 1 || A[i] == 0)	// 배열의 끝까지 이르면 종료
			break;

		if (i == 1)		// level 1
			printf("\t\t\t%d\n\n", A[i]);
		else if (i >= len / 2 / 2 / 2 + 1 && i <= len / 2 / 2) {	// level 2
			printf("\t\t%d", A[i]);
			if (i == len / 2 / 2)
				printf("\n\n");
		}
		else if (i >= len / 2 / 2 + 1 && i <= len / 2) {		// level 3
			printf("\t    %d", A[i]);
			if (i == len / 2)
				printf("\n\n\t");
		}
		else if (i >= len / 2 + 1 && i <= len) {		// level 4
			printf("   %d", A[i]);
		}
		i++;		// 다음 index로 이동
	}
	printf("\n-----------------------------------------------------\n");
}
int Parent(int i)
{
	return i / 2;
}
int Left(int i)
{
	return i * 2;
}
int Right(int i)
{
	return i * 2 + 1;
}
void PRINT_ARRAY(int A[])
{
	for (int i = 1; i <= len; i++)	// 0번째 index는 X
		if(A[i] !=0)
			printf("%d ", A[i]);
	printf("\n");
}
int Arrlength(int A[])
{
	int length = 0;

	while (1)
	{
		if (A[length] == 0)	// index를 하나씩 증가시키다가
			break;			// 끝에 이르면 종료
		length++;
	}
	length--;			// 배열의 길이 + 1 되어있으므로 하나 빼줌
	
	return length;
}
