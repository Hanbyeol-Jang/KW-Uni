#include "MaxHeap.h"					//MaxHeap ��� ����

int main()
{
	MaxHeap<int> H;						//��ü H ����

	for (int i = 1; i <= 10; i++)		//1���� 10����
		H.Push(i);						//MaxHeap ���� ����

	H.GetHeap();						//GetHeap �Լ� ȣ��� Ʈ�� �� ���� ���
	cout << endl;

	H.Pop();							//Ʈ�� �� Root ����
	H.GetHeap();						//GetHeap �Լ� ȣ��� Ʈ�� �� ���� ���
	cout << endl;

	H.Pop();							//Ʈ�� �� Root ����
	H.GetHeap();						//GetHeap �Լ� ȣ��� Ʈ�� �� ���� ���
	cout << endl;

	return 0;
}