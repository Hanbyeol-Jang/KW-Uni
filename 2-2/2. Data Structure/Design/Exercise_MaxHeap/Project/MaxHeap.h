#pragma once
#include <iostream>
#include <algorithm>						//algorithm 헤더 참조
using namespace std;

template <class T>							//템플릿 선언
class MaxHeap								//클래스 선언
{
public:

	MaxHeap (int theCapacity = 10);			//MaxHeap 생성자
	~MaxHeap() {}

	void Push(const T&e);												//Push 함수 선언
	void ChangeSize1D(T*&a, const int oldSize, const int newSize);		//ChangeSize1D 함수 선언
	void Pop();								 //Pop 함수 선언
	void GetHeap();							 //GetHeap 함수 선언

	bool IsEmpty()						     //IsEmpty 함수 선언
	{
		if (heap[1] == NULL)				 //heap[1]이 NULL 이라면 1 반환
			return 1;
		else								 //heap[1]이 NULL이 아니라면 0반환
			return 0;
	}

private:
	T *heap;								 // heap
	int heapSize;							 // heap 원소의 수
	int capacity;							 // heap 배열의 크기

};

template <class T>
MaxHeap<T>::MaxHeap(int theCapacity = 10)		//MaxHeap 생성자 정의
{
	if (theCapacity < 1)
		throw "Capacity must be >= 1. ";		//heapSize==0 이면 공백
	capacity = theCapacity;						//최대 히프의 최대 원소는 heap[1]
	heapSize = 0;
	heap = new T[capacity + 1];					//heap[0]은 사용하지 않으므로 NULL
}

template <class T>
void MaxHeap<T>::Push(const T&e)				//새로운 원소를 삽입시키기 위한 Push 함수 정의
{
	if (heapSize == capacity)
	{															//최대 히프에 e를 삽입
		ChangeSize1D(heap, capacity, 2 * capacity);				//크기를 두 배로
		capacity *= 2;
	}

	int currentNode = ++heapSize;
	while (currentNode != 1 && heap[currentNode / 2] < e)
	{															//Root로 올라감
		heap[currentNode] = heap[currentNode / 2];				//부모 노드로 이동
		currentNode /= 2;
	}
	heap[currentNode] = e;

}

template <class T>	
void MaxHeap<T>::ChangeSize1D(T*&a, const int oldSize, const int newSize)		//ChangeSize1D 함수 정의
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
void MaxHeap<T>::Pop()								//트리 내의 root를 삭제하는 Pop 함수 정의
{
	if (IsEmpty()) throw "Heap is empty. Cannot delete. ";
	heap[1].~T();												//최대 원소 삭제

	T lastE = heap[heapSize--];									//heap 의 마지막 원소 제거

	int currentNode = 1;										//루트
	int child = 2;												//currentNode의 자식

	while (child <= heapSize)
	{															//child를 currentNode 의 큰 자식으로 결정
		if (child < heapSize&&heap[child] < heap[child + 1])child++;
																//currentNode에 lastE를 삽입할 수 있는가?
		if (lastE >= heap[child]) break;						//yes

		heap[currentNode] = heap[child];						//no
		currentNode = child;									//자식으로 이동
		child *= 2;												//한 레벨 내려감
	}

	heap[currentNode] = lastE;
}

template<class T>
void MaxHeap<T>::GetHeap()							//트리 원소를 출력하는 GetHeap 함수 정의
{
	for (int i = 1; i <= heapSize; i++)				//heap[0]==NULL 이므로
		cout << heap[i] << " ";						//heap[1]부터 출력
}
