#include "addition.h"

int MAX_HEAPIFY(int A[], int i); // MAX Heap 화하는 함수
void BUILD_MAX_HEAP(int A[]);
void HEAPSORT(int A[]);

int main(void)
{
	// index 계산의 간편함을 위해 0 자리에 99999999 삽입 
	int A[16] = {99999999, 4, 1, 3, 2, 16, 9, 10, 14, 8, 7};

	printf("INPUT: ");
	PRINT_ARRAY(A);
	HEAPSORT(A);

	return 0;
}

int MAX_HEAPIFY(int A[], int i)
{
	i = Parent(i);		// i번째 값이 그 parent의 값보다 클 때 함수가 호출되므로
	if (i == 0)
		return 1;
	int larger = 0;		// 변수 초기화
	int temp = 0;
	int l = 0, r = 0;
	int length = 0;
	l = Left(i);		// left child
	r = Right(i);		// right child
	length = Arrlength(A);

	if (l <= length && A[l] > A[i])	// left child가 더 큰 경우
		larger = l;		// left child 를 더 큰 값에
	else
		larger = i;		// 그대로

	if (r <= length && A[r] > A[larger])	// right child가 더 큰 경우
		larger = r;		// right child 를 더 큰 값에

	if (larger != i)	// parent가 child 보다 큰 상황
	{
		temp = A[i];		// swap parent with child
		A[i] = A[larger];
		A[larger] = temp;
		MAX_HEAPIFY(A, temp);		// sub tree 까지 확인을 위해 재귀 함수 호출
	}
	return 1;
}
void BUILD_MAX_HEAP(int A[])
{
	int i = 1, j = 0;
	int length = 0;
	length = Arrlength(A);
	j = length / 2;	// build 시 leaf node 들은 Max Heapify 해줄 필요 없음

	while (1)
	{
		if (j < 1)	// 배열의 끝까지 이르면 종료
			break;

		i = 1;	// Build 를 위한 index 초기화

		while (1)
		{
			if (i == length + 1 || A[i] == 0)	// 배열의 끝까지 이르면 종료
				break;

			if (A[Parent(i)] < A[i])	// 해당 값이 parent 보다 클 때
			{
				MAX_HEAPIFY(A, i);
				i = 1;		// index 초기화
				continue;
			}
			i++;	// index 하나씩 증가
		}
		j--;
	}
}
void HEAPSORT(int A[])
{
	int i = 0;
	int temp = 0;
	int temparr[16] = { 100, };

	BUILD_MAX_HEAP(A);

	int length = 0;				// 마지막 index에 접근 하기위해
	length = Arrlength(A);		// 배열의 길이 저장
	
	while (1)
	{
		if (length < 1)
			break;

		printf("[MAX HEAPIFY]\n");
		PRINT_ARRAY(A);	
		PRINT_TREE(A);

		temp = A[1];			// root 와
		A[1] = A[length];		// 가장 마지막 index에 있는 값
		A[length] = temp;		// 교환

		printf("[SWAP]\n");
		PRINT_ARRAY(A);
		PRINT_TREE(A);

		temparr[length] = A[length]; // 가장 큰 수가 배열 마지막에 위치하게
		A[length] = 0;			// 빠진 자리 0으로 채움
		length--;				// 가장 큰 수 빼줬으니 -1

		BUILD_MAX_HEAP(A);		// 다시 Heap화 한다
	}

	A = temparr;			// temp에 넣어놨던 가장 큰 수 옮김
	printf("OUTPUT: ");
	PRINT_ARRAY(A);
}
