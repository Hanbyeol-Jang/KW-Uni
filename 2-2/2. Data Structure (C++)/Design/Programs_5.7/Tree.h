#pragma once
#include "Queue.h"										      //Stack 헤더 참조

template<class T>                                             //템플릿 선언
class Tree : public TreeNode<T>								  //클래스 선언 
{
public:
	Tree()
	{
		TreeNode<T> *pNode1 = new TreeNode<T>();               //총 9개의 TreeNode를 생성
		TreeNode<T> *pNode2 = new TreeNode<T>();
		TreeNode<T> *pNode3 = new TreeNode<T>();
		TreeNode<T> *pNode4 = new TreeNode<T>();
		TreeNode<T> *pNode5 = new TreeNode<T>();
		TreeNode<T> *pNode6 = new TreeNode<T>();
		TreeNode<T> *pNode7 = new TreeNode<T>();
		TreeNode<T> *pNode8 = new TreeNode<T>();
		TreeNode<T> *pNode9 = new TreeNode<T>();
		root = pNode1;                                        //root 에 pNode1의 주솟값넣어줌

		pNode1->leftChild = pNode2;                           //Textbook 그림 5.16. 처럼 연결
		pNode1->rightChild = pNode3;
		pNode2->leftChild = pNode4;
		pNode2->rightChild = pNode5;
		pNode4->leftChild = pNode6;
		pNode4->rightChild = pNode7;
		pNode6->leftChild = pNode8;
		pNode6->rightChild = pNode9;

		pNode1->Setdata('+');                                //Setdata함수를 통해 각 Node마다 값을 넣어줌.
		pNode2->Setdata('*');
		pNode3->Setdata('E');
		pNode4->Setdata('*');
		pNode5->Setdata('D');
		pNode6->Setdata('/');
		pNode7->Setdata('C');
		pNode8->Setdata('A');
		pNode9->Setdata('B');

	}

	~Tree()
	{

	}

	void Visit(TreeNode<T> *currentNode)                        //Visit 함수 선언
	{
		cout << currentNode->Getdata() << " ";                  //currentNode의 data를 출력
	}

	void Levelorder()                                                        // Queue를 이용한 Levelorder 순회방법 구현
	{
		Queue<char> q;                                                       //Queue 선언
		TreeNode<T> *currentNode = root;                                     //currentNode에 root 주솟값 대입
		while (currentNode)
		{
			Visit(currentNode);											     //currentNode를 입력 형태로하는 Visit함수 호출
			if (currentNode->leftChild)q.Push(currentNode->leftChild);       //currentNode에 leftChild가 있으면, currentNode의 leftChild를 큐에 삽입
			if (currentNode->rightChild)q.Push(currentNode->rightChild);     //currentNode에 rightChild가 있으면, currentNode의 rightChild를 큐에 삽입
			if (q.IsEmpty()) return;                                         //큐가 비어있으면 상황 종료
			currentNode = q.Front();                                         //currentNode를 큐의 헤드로 초기화
			q.Pop();                                                         //큐에서의 삭제
		}
	}

	TreeNode *GetRoot()                                         //GetRoot 함수 선언
	{
		return root;                                            //root 반환
	}

protected:                                                      //root를 protected로 선언
	TreeNode<T> *root;                                          // root 선언

};