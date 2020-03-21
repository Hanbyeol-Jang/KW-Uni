#pragma once
#include <iostream>
#include <algorithm>						//algorithm ��� ����
using namespace std;

template <class T>							//���ø� ����
class MaxHeap								//Ŭ���� ����
{
public:

	MaxHeap (int theCapacity = 10);			//MaxHeap ������
	~MaxHeap() {}

	void Push(const T&e);												//Push �Լ� ����
	void ChangeSize1D(T*&a, const int oldSize, const int newSize);		//ChangeSize1D �Լ� ����
	void Pop();								 //Pop �Լ� ����
	void GetHeap();							 //GetHeap �Լ� ����

	bool IsEmpty()						     //IsEmpty �Լ� ����
	{
		if (heap[1] == NULL)				 //heap[1]�� NULL �̶�� 1 ��ȯ
			return 1;
		else								 //heap[1]�� NULL�� �ƴ϶�� 0��ȯ
			return 0;
	}

private:
	T *heap;								 // heap
	int heapSize;							 // heap ������ ��
	int capacity;							 // heap �迭�� ũ��

};

template <class T>
MaxHeap<T>::MaxHeap(int theCapacity = 10)		//MaxHeap ������ ����
{
	if (theCapacity < 1)
		throw "Capacity must be >= 1. ";		//heapSize==0 �̸� ����
	capacity = theCapacity;						//�ִ� ������ �ִ� ���Ҵ� heap[1]
	heapSize = 0;
	heap = new T[capacity + 1];					//heap[0]�� ������� �����Ƿ� NULL
}

template <class T>
void MaxHeap<T>::Push(const T&e)				//���ο� ���Ҹ� ���Խ�Ű�� ���� Push �Լ� ����
{
	if (heapSize == capacity)
	{															//�ִ� ������ e�� ����
		ChangeSize1D(heap, capacity, 2 * capacity);				//ũ�⸦ �� ���
		capacity *= 2;
	}

	int currentNode = ++heapSize;
	while (currentNode != 1 && heap[currentNode / 2] < e)
	{															//Root�� �ö�
		heap[currentNode] = heap[currentNode / 2];				//�θ� ���� �̵�
		currentNode /= 2;
	}
	heap[currentNode] = e;

}

template <class T>	
void MaxHeap<T>::ChangeSize1D(T*&a, const int oldSize, const int newSize)		//ChangeSize1D �Լ� ����
{
	if (newSize < 0)
		throw " New length must be >= 0";

	T *temp = new T[newSize];
	int number = min(oldSize, newSize);
	copy(a, a + number, temp);
	delete[]a;
	a = temp;

}

template<class T>
void MaxHeap<T>::Pop()								//Ʈ�� ���� root�� �����ϴ� Pop �Լ� ����
{
	if (IsEmpty()) throw "Heap is empty. Cannot delete. ";
	heap[1].~T();												//�ִ� ���� ����

	T lastE = heap[heapSize--];									//heap �� ������ ���� ����

	int currentNode = 1;										//��Ʈ
	int child = 2;												//currentNode�� �ڽ�

	while (child <= heapSize)
	{															//child�� currentNode �� ū �ڽ����� ����
		if (child < heapSize&&heap[child] < heap[child + 1])child++;
																//currentNode�� lastE�� ������ �� �ִ°�?
		if (lastE >= heap[child]) break;						//yes

		heap[currentNode] = heap[child];						//no
		currentNode = child;									//�ڽ����� �̵�
		child *= 2;												//�� ���� ������
	}

	heap[currentNode] = lastE;
}

template<class T>
void MaxHeap<T>::GetHeap()							//Ʈ�� ���Ҹ� ����ϴ� GetHeap �Լ� ����
{
	for (int i = 1; i <= heapSize; i++)				//heap[0]==NULL �̹Ƿ�
		cout << heap[i] << " ";						//heap[1]���� ���
}
