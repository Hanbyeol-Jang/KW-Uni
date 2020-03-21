#pragma once
#include "TreeNode.h"								//TreeNode ��� ����

template<class K, class E>							//���ø� ����
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
	void Delete(K&k);

	void Visit(TreeNode<pair<K, E>> *currentNode)				//Visit �Լ�����
	{

		cout << currentNode->Getdata().first << " ";			//currentNode�� data�� ���
	}

	void Inorder()												//Inorder �Լ� ����
	{
		Inorder(root);
	}

	void Inorder(TreeNode<pair<K, E>> *currentNode)			    //Inorder ��ȸ ��� ����
	{
		if (currentNode)
		{
			Inorder(currentNode->leftChild);				    //curruentNode�� leftchild �� �Է� ���·��ϴ� Inorder �Լ� ȣ�� 
			Visit(currentNode);								    //currentNode�� �Է����·��ϴ� Visit �Լ� ȣ��
			Inorder(currentNode->rightChild);				    //curruentNode�� rightchild �� �Է� ���·��ϴ� Inorder �Լ� ȣ��
		}

	}

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

template<class K, class E>                                       //���ø� ����
void BST<K, E>::Delete(K& k)                                     //Delete �Լ� ����
{
	TreeNode<pair<K, E>> *p = root, *q = 0;                      //p ���� �� root�� �ʱ�ȭ,q ���� �� 0���� �ʱ�ȭ
	while (p && k != p->s_data.first)                            //root�� �����ϰ�,�Է¹���k�� root�� �����Ϳ� ���� ������ �ݺ��� ����
	{
		q = p; 
		if (k < p->s_data.first) p = p->leftChild;               //�Է¹��� k�� data�� key���� ���� ��, p�� leftChild�� �̵�
		else p = p->rightChild;                                  //�Է¹��� k�� data�� key���� Ŭ ��, p�� rightChild�� �̵�
	}

	if (p == 0)return;

	if (p->leftChild == 0 && p->rightChild == 0)                 //p�� leaf��� Child delete
	{
		if (q == 0)root = 0;
		else if (q->leftChild == p)q->leftChild = 0;
		else q->rightChild = 0;
		delete p;
		return;
	}

	if (p->leftChild == 0)										 //p�� rightChild�� ������ ���� ��, Child delete
	{
		if (q == 0) root = p->rightChild;
		else if (q->leftChild == p) q->leftChild = p->rightChild;
		else q->rightChild = p->rightChild;
		delete p;
		return;
	}

	if (p->rightChild == 0)										 //p�� leftChild�� ������ ���� ��, Child delete
	{
		if (q == 0) root = p->leftChild;
		else if (q->leftChild == p) q->leftChild = p->leftChild;
		else q->rightChild = p->leftChild;
		delete p;
		return;
	}

	TreeNode<pair<K, E>> *prevprev = p, *prev = p->rightChild, *curr = p->rightChild->leftChild;       //������ Node�� �ΰ��� Child�� ������ ���� ��, Child delete
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