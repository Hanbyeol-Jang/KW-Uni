#pragma once
#include "TreeNode.h"								//TreeNode ��� ����

template<class K,class E>							//���ø� ����
class BST											//Ŭ���� ����
{
public:
	BST() 
	{
		root = NULL;								//root�� NULL�� �ʱ�ȭ
	}

	~BST()
	{

	}

	void Insert(pair<K, E>&thePair);							//Insert �Լ� ����
	pair<K, E> *Get(const K&k);								    //��ȯ�� Ž�� driver
	pair<K, E> *Get(TreeNode<pair<K, E>> *p, const K&k);		//��ȯ�� Ž�� workhorse

private:
	TreeNode<pair<K, E>> *root;									 //��� ���� ����
};

template<class K, class E>
void BST<K, E>::Insert(pair<K, E> &thePair)						     //Insert �Լ� ����
{
	TreeNode<pair<K, E>> *p = root, *pp = 0;					     //p�� root, pp�� 0���� �ʱ�ȭ

	while (p)
	{
		pp = p;
		if (thePair.first < p->s_data.first)					     //pp�� p�� �θ�, thePair �� firstŽ��
			p = p->leftChild;									     //root�� ������ �Է¹��� �����Ͱ� ���� ��, p�� leftChild�� �̵�
		else if (thePair.first > p->s_data.first)				     //root�� ������ �Է¹��� �����Ͱ� Ŭ ��, p�� rightChild�� �̵�
			p = p->rightChild;
		else
		{
			p->s_data.second = thePair.second;
			return;
		}
	}

	p = new TreeNode<pair<K, E>>(thePair);						     //thePair�� ���ο� �����Ҵ����� Node ����

	if (root)
		if (thePair.first < pp->s_data.first)pp->leftChild = p;		 //root�� ������ �Է¹��� �����Ͱ� ������� p�� leftChild�� �̵�
		else pp->rightChild = p;									 //p�� rightChild �� �̵�
	else root = p;													 //root�� ������ p�� root�� ����
}

template<class K, class E>
pair<K, E> *BST<K, E>::Get(const K&k)								 //��ȯ�� Ž�� driver
{
	return Get(root, k);
}

template<class K, class E>
pair<K, E> *BST<K, E>::Get(TreeNode<pair<K, E>> *p, const K&k)		 //��ȯ�� Ž�� workhorse
{
	if (!p) return 0;
	if (k < p->s_data.first) return Get(p->leftChild, k);			 //leftChild�� �̵�
	if (k > p->s_data.first) return Get(p->rightChild, k);			 //rightChild�� �̵�
	return &p->s_data;
};