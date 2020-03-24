#include <iostream>
using namespace std;
#define len 15

void PRINT_TREE(int A[]);		// �迭�� Tree ������� ����ϴ� �Լ�
int Parent(int i);		// Tree���� i index�� node �� parent node�� index�� �������� �Լ�
int Left(int i);		// ���� child �� index�� �������� �Լ�
int Right(int i);		// ������ child �� index�� �������� �Լ�
void PRINT_ARRAY(int A[]); // �迭�� ��� ��ҵ��� ���������� ����ϴ� �Լ�
int Arrlength(int A[]);		// �迭�� ���̸� �������� �Լ�

void PRINT_TREE(int A[])
{
	int i = 1;	// �Էµ� �迭�� ù��° ��� ����
	while (1)
	{
		if (i == len + 1 || A[i] == 0)	// �迭�� ������ �̸��� ����
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
		i++;		// ���� index�� �̵�
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
	for (int i = 1; i <= len; i++)	// 0��° index�� X
		if(A[i] !=0)
			printf("%d ", A[i]);
	printf("\n");
}
int Arrlength(int A[])
{
	int length = 0;

	while (1)
	{
		if (A[length] == 0)	// index�� �ϳ��� ������Ű�ٰ�
			break;			// ���� �̸��� ����
		length++;
	}
	length--;			// �迭�� ���� + 1 �Ǿ������Ƿ� �ϳ� ����
	
	return length;
}
