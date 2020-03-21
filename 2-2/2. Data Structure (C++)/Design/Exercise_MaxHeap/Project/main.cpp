#include "MaxHeap.h"					//MaxHeap 헤더 참조

int main()
{
	MaxHeap<int> H;						//객체 H 생성

	for (int i = 1; i <= 10; i++)		//1부터 10까지
		H.Push(i);						//MaxHeap 원소 삽입

	H.GetHeap();						//GetHeap 함수 호출시 트리 내 원소 출력
	cout << endl;

	H.Pop();							//트리 내 Root 삭제
	H.GetHeap();						//GetHeap 함수 호출시 트리 내 원소 출력
	cout << endl;

	H.Pop();							//트리 내 Root 삭제
	H.GetHeap();						//GetHeap 함수 호출시 트리 내 원소 출력
	cout << endl;

	return 0;
}