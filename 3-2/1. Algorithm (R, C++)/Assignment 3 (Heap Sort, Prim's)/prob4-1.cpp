#include "addition.h"

int MAX_HEAPIFY(int A[], int i); // MAX Heap ȭ�ϴ� �Լ�
void BUILD_MAX_HEAP(int A[]);
void HEAPSORT(int A[]);

int main(void)
{
	// index ����� �������� ���� 0 �ڸ��� 99999999 ���� 
	int A[16] = {99999999, 4, 1, 3, 2, 16, 9, 10, 14, 8, 7};

	printf("INPUT: ");
	PRINT_ARRAY(A);
	HEAPSORT(A);

	return 0;
}

int MAX_HEAPIFY(int A[], int i)
{
	i = Parent(i);		// i��° ���� �� parent�� ������ Ŭ �� �Լ��� ȣ��ǹǷ�
	if (i == 0)
		return 1;
	int larger = 0;		// ���� �ʱ�ȭ
	int temp = 0;
	int l = 0, r = 0;
	int length = 0;
	l = Left(i);		// left child
	r = Right(i);		// right child
	length = Arrlength(A);

	if (l <= length && A[l] > A[i])	// left child�� �� ū ���
		larger = l;		// left child �� �� ū ����
	else
		larger = i;		// �״��

	if (r <= length && A[r] > A[larger])	// right child�� �� ū ���
		larger = r;		// right child �� �� ū ����

	if (larger != i)	// parent�� child ���� ū ��Ȳ
	{
		temp = A[i];		// swap parent with child
		A[i] = A[larger];
		A[larger] = temp;
		MAX_HEAPIFY(A, temp);		// sub tree ���� Ȯ���� ���� ��� �Լ� ȣ��
	}
	return 1;
}
void BUILD_MAX_HEAP(int A[])
{
	int i = 1, j = 0;
	int length = 0;
	length = Arrlength(A);
	j = length / 2;	// build �� leaf node ���� Max Heapify ���� �ʿ� ����

	while (1)
	{
		if (j < 1)	// �迭�� ������ �̸��� ����
			break;

		i = 1;	// Build �� ���� index �ʱ�ȭ

		while (1)
		{
			if (i == length + 1 || A[i] == 0)	// �迭�� ������ �̸��� ����
				break;

			if (A[Parent(i)] < A[i])	// �ش� ���� parent ���� Ŭ ��
			{
				MAX_HEAPIFY(A, i);
				i = 1;		// index �ʱ�ȭ
				continue;
			}
			i++;	// index �ϳ��� ����
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

	int length = 0;				// ������ index�� ���� �ϱ�����
	length = Arrlength(A);		// �迭�� ���� ����
	
	while (1)
	{
		if (length < 1)
			break;

		printf("[MAX HEAPIFY]\n");
		PRINT_ARRAY(A);	
		PRINT_TREE(A);

		temp = A[1];			// root ��
		A[1] = A[length];		// ���� ������ index�� �ִ� ��
		A[length] = temp;		// ��ȯ

		printf("[SWAP]\n");
		PRINT_ARRAY(A);
		PRINT_TREE(A);

		temparr[length] = A[length]; // ���� ū ���� �迭 �������� ��ġ�ϰ�
		A[length] = 0;			// ���� �ڸ� 0���� ä��
		length--;				// ���� ū �� �������� -1

		BUILD_MAX_HEAP(A);		// �ٽ� Heapȭ �Ѵ�
	}

	A = temparr;			// temp�� �־���� ���� ū �� �ű�
	printf("OUTPUT: ");
	PRINT_ARRAY(A);
}
