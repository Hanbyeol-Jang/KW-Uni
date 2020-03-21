#pragma once
#include "Stack.h"										      //Stack 헤더 참조

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

	void Inorder()                                              //Inorder 함수 선언
	{
		Inorder(root);                                          //처음 Inorder 함수로 들어갈 때, 입력에 root를 넣어주도록 설정
	}

	void Inorder(TreeNode<T> *currentNode)                      //재귀함수를 통하여 Inorder순회방법 구현
	{
		if (currentNode)
		{
			Inorder(currentNode->leftChild);                    //currentNode의 leftChild를 입력 형태로하는 Inorder함수 호출 
			Visit(currentNode);                                 //currentNode를 입력 형태로하는 Visit함수 호출
			Inorder(currentNode->rightChild);                   //currentNode의 rightChild를 입력 형태로하는 Inorder함수 호출
		}
	}

	TreeNode *GetRoot()                                         //GetRoot 함수 선언
	{
		return root;                                            //root 반환
	}
	 
protected:                                                      //root를 protected로 선언
	TreeNode<T> *root;                                          // root 선언

};