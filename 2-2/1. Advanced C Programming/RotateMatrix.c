#include <stdio.h>
#define ARR_SIZE 5								 //ARR_SIZE를 5로 정의

void ShiftToLeft();								 //ShiftToLeft 함수 선언
void ShiftToRight();							 //ShiftToRight 함수 선언
void RotateToLeft();							 //RotateToLeft 함수 선언
void RotateToRight();							 //RotateToRight 함수 선언

int main(void)
{
	int row=0, col=0;							 //int형 변수 row, col 선언 과 동시에 0으로 초기화
	int i = 0;									 //int형 변수 i 선언과 동시에 0으로 초기화

	int arr2D[ARR_SIZE][ARR_SIZE] =
	{
		{1,  2,  3,  4,  5},
		{6,  7,  8,  9,  10},
		{11, 12, 13, 14, 15},
		{16, 17, 18, 19, 20},
		{21, 22, 23, 24, 25},
	};											 //int형 5X5 2차원 배열 arr2D 선언과 동시에 초기화

	int temp = 0;								 //int형 변수 temp 선언과 동시에 0으로 초기화

	//ShiftToLeft(row, col, arr2D, temp);		 //ShiftToLeft 함수 호출
	//ShiftToRight(row, col, arr2D, temp);		 //ShiftToRight 함수 호출
	//RotateToLeft(i, arr2D, temp);				 //RotateToLeft 함수 호출
	RotateToRight(i, arr2D, temp);			 //RotateToRight 함수 호출

	for (row = 0; row < ARR_SIZE; row++)		 //2차원 배열 출력
	{
		for (col = 0; col < ARR_SIZE; col++)
			printf("%2d ", arr2D[row][col]);
		printf("\n");
	}
	printf("\n");

	return 0;
}

void ShiftToLeft(int row, int col, int arr2D[ARR_SIZE][ARR_SIZE], int temp)		//ShiftToLeft 함수 정의
{
	for (row = 0; row < ARR_SIZE; row++)
	{
		temp = arr2D[row][0];

		for (col = 0; col < ARR_SIZE - 1; col++)
		{
			arr2D[row][col] = arr2D[row][col + 1];
		}
		arr2D[row][ARR_SIZE - 1] = temp;
	}
}

void ShiftToRight(int row, int col, int arr2D[ARR_SIZE][ARR_SIZE], int temp)	//ShiftToRight 함수 정의
{
	for (row = 0; row < ARR_SIZE; row++)
	{
		temp = arr2D[row][ARR_SIZE - 1];

		for (col = ARR_SIZE - 1; col > 0; col--)
		{
			arr2D[row][col] = arr2D[row][col - 1];
		}
		arr2D[row][0] = temp;
	}
}

void RotateToLeft(int i, int arr2D[ARR_SIZE][ARR_SIZE], int temp)	//RotateToLeft 함수 정의
{
	for (i = 0; i < 4; i++)
	{
		temp = arr2D[0][i];
		arr2D[0][i]		= arr2D[i][4];
		arr2D[i][4]		= arr2D[4][4 - i];
		arr2D[4][4 - i] = arr2D[4 - i][0];
		arr2D[4 - i][0] = temp;
	}

	for (i = 1; i < 3; i++)
	{
		temp			= arr2D[1][i];
		arr2D[1][i]		= arr2D[i][3];
		arr2D[i][3]		= arr2D[3][4 - i];
		arr2D[3][4 - i] = arr2D[4 - i][1];
		arr2D[4 - i][1] = temp;
	}
}	

void RotateToRight(int i, int arr2D[ARR_SIZE][ARR_SIZE], int temp)	//RotateToRight 함수 정의
{
	for (i = 0; i < 4; i++)
	{
		temp			= arr2D[0][i];
		arr2D[0][i]		= arr2D[4 - i][0];
		arr2D[4 - i][0] = arr2D[4][4 - i];
		arr2D[4][4 - i] = arr2D[i][4];
		arr2D[i][4]		= temp;
	}

	for (i = 1; i < 3; i++)
	{
		temp			= arr2D[1][i];
		arr2D[1][i]		= arr2D[4 - i][1];
		arr2D[4 - i][1] = arr2D[3][4 - i];
		arr2D[3][4 - i] = arr2D[i][3];
		arr2D[i][3]		= temp;
	}
}