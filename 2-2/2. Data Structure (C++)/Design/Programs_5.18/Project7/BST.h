#pragma once
#include "TreeNode.h"								//TreeNode 헤더 참조

template<class K,class E>							//템플릿 선언
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