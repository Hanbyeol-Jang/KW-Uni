#include <stdio.h>
#define ARR_SIZE 5								 //ARR_SIZE�� 5�� ����

void ShiftToLeft();								 //ShiftToLeft �Լ� ����
void ShiftToRight();							 //ShiftToRight �Լ� ����
void RotateToLeft();							 //RotateToLeft �Լ� ����
void RotateToRight();							 //RotateToRight �Լ� ����

int main(void)
{
	int row=0, col=0;							 //int�� ���� row, col ���� �� ���ÿ� 0���� �ʱ�ȭ
	int i = 0;									 //int�� ���� i ����� ���ÿ� 0���� �ʱ�ȭ

	int arr2D[ARR_SIZE][ARR_SIZE] =
	{
		{1,  2,  3,  4,  5},
		{6,  7,  8,  9,  10},
		{11, 12, 13, 14, 15},
		{16, 17, 18, 19, 20},
		{21, 22, 23, 24, 25},
	};											 //int�� 5X5 2���� �迭 arr2D ����� ���ÿ� �ʱ�ȭ

	int temp = 0;								 //int�� ���� temp ����� ���ÿ� 0���� �ʱ�ȭ

	//ShiftToLeft(row, col, arr2D, temp);		 //ShiftToLeft �Լ� ȣ��
	//ShiftToRight(row, col, arr2D, temp);		 //ShiftToRight �Լ� ȣ��
	//RotateToLeft(i, arr2D, temp);				 //RotateToLeft �Լ� ȣ��
	RotateToRight(i, arr2D, temp);			 //RotateToRight �Լ� ȣ��

	for (row = 0; row < ARR_SIZE; row++)		 //2���� �迭 ���
	{
		for (col = 0; col < ARR_SIZE; col++)
			printf("%2d ", arr2D[row][col]);
		printf("\n");
	}
	printf("\n");

	return 0;
}

void ShiftToLeft(int row, int col, int arr2D[ARR_SIZE][ARR_SIZE], int temp)		//ShiftToLeft �Լ� ����
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

void ShiftToRight(int row, int col, int arr2D[ARR_SIZE][ARR_SIZE], int temp)	//ShiftToRight �Լ� ����
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

void RotateToLeft(int i, int arr2D[ARR_SIZE][ARR_SIZE], int temp)	//RotateToLeft �Լ� ����
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

void RotateToRight(int i, int arr2D[ARR_SIZE][ARR_SIZE], int temp)	//RotateToRight �Լ� ����
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