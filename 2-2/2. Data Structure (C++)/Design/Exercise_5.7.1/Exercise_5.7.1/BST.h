#pragma once
#include "TreeNode.h"								//TreeNode 헤더 참조

template<class K, class E>							//템플릿 선언
class BST											//클래스 선언
{
public:
	BST()
	{
		root = NULL;								//root를 NULL로 초기화
	}

	~BST()
	{

	}

	void Insert(pair<K, E>&thePair);							//Insert 함수 선언
	pair<K, E> *Get(const K&k);								    //순환적 탐색 driver
	pair<K, E> *Get(TreeNode<pair<K, E>> *p, const K&k);		//순환적 탐색 workhorse
	void Delete(K&k);

	void Visit(TreeNode<pair<K, E>> *currentNode)				//Visit 함수선언
	{

		cout << currentNode->Getdata().first << " ";			//currentNode의 data를 출력
	}

	void Inorder()												//Inorder 함수 선언
	{
		Inorder(root);
	}

	void Inorder(TreeNode<pair<K, E>> *currentNode)			    //Inorder 순회 방법 구현
	{
		if (currentNode)
		{
			Inorder(currentNode->leftChild);				    //curruentNode의 leftchild 를 입력 형태로하는 Inorder 함수 호출 
			Visit(currentNode);								    //currentNode를 입력형태로하는 Visit 함수 호출
			Inorder(currentNode->rightChild);				    //curruentNode의 rightchild 를 입력 형태로하는 Inorder 함수 호출
		}

	}

private:
	TreeNode<pair<K, E>> *root;									 //멤버 변수 선언
};

template<class K, class E>
void BST<K, E>::Insert(pair<K, E> &thePair)						     //Insert 함수 선언
{
	TreeNode<pair<K, E>> *p = root, *pp = 0;					     //p를 root, pp를 0으로 초기화

	while (p)
	{
		pp = p;
		if (thePair.first < p->s_data.first)					     //pp는 p의 부모, thePair 의 first탐색
			p = p->leftChild;									     //root의 값보다 입력받은 데이터가 작을 시, p는 leftChild로 이동
		else if (thePair.first > p->s_data.first)				     //root의 값보다 입력받은 데이터가 클 시, p는 rightChild로 이동
			p = p->rightChild;
		else
		{
			p->s_data.second = thePair.second;
			return;
		}
	}

	p = new TreeNode<pair<K, E>>(thePair);						     //thePair를 새로운 동적할당으로 Node 생성

	if (root)
		if (thePair.first < pp->s_data.first)pp->leftChild = p;		 //root의 값보다 입력받은 데이터가 작을경우 p는 leftChild로 이동
		else pp->rightChild = p;									 //p는 rightChild 로 이동
	else root = p;													 //root가 없으면 p를 root로 설정
}

template<class K, class E>
pair<K, E> *BST<K, E>::Get(const K&k)								 //순환적 탐색 driver
{
	return Get(root, k);
}

template<class K, class E>
pair<K, E> *BST<K, E>::Get(TreeNode<pair<K, E>> *p, const K&k)		 //순환적 탐색 workhorse
{
	if (!p) return 0;
	if (k < p->s_data.first) return Get(p->leftChild, k);			 //leftChild로 이동
	if (k > p->s_data.first) return Get(p->rightChild, k);			 //rightChild로 이동
	return &p->s_data;
};

template<class K, class E>                                       //템플릿 선언
void BST<K, E>::Delete(K& k)                                     //Delete 함수 선언
{
	TreeNode<pair<K, E>> *p = root, *q = 0;                      //p 선언 후 root로 초기화,q 선언 후 0으로 초기화
	while (p && k != p->s_data.first)                            //root가 존재하고,입력받은k가 root의 데이터와 같지 않을때 반복문 진입
	{
		q = p; 
		if (k < p->s_data.first) p = p->leftChild;               //입력받은 k가 data의 key보다 작을 시, p를 leftChild로 이동
		else p = p->rightChild;                                  //입력받은 k가 data의 key보다 클 시, p를 rightChild로 이동
	}

	if (p == 0)return;

	if (p->leftChild == 0 && p->rightChild == 0)                 //p가 leaf라면 Child delete
	{
		if (q == 0)root = 0;
		else if (q->leftChild == p)q->leftChild = 0;
		else q->rightChild = 0;
		delete p;
		return;
	}

	if (p->leftChild == 0)										 //p가 rightChild만 가지고 있을 시, Child delete
	{
		if (q == 0) root = p->rightChild;
		else if (q->leftChild == p) q->leftChild = p->rightChild;
		else q->rightChild = p->rightChild;
		delete p;
		return;
	}

	if (p->rightChild == 0)										 //p가 leftChild만 가지고 있을 시, Child delete
	{
		if (q == 0) root = p->leftChild;
		else if (q->leftChild == p) q->leftChild = p->leftChild;
		else q->rightChild = p->leftChild;
		delete p;
		return;
	}

	TreeNode<pair<K, E>> *prevprev = p, *prev = p->rightChild, *curr = p->rightChild->leftChild;       //삭제할 Node가 두개의 Child를 가지고 있을 시, Child delete
	while (curr)
	{
		prevprev = prev;
		prev = curr;
		curr = curr->leftChild;
	}

	p->s_data = prev->s_data;
	if (prevprev == p)prevprev->rightChild = prev->rightChild;
	else prevprev->leftChild = prev->rightChild;
	delete prev;
	return;
}