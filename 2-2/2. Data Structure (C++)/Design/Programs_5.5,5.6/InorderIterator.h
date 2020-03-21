#pragma once
#include<iostream>                          
#include"TreeNode.h"								//TreeNode ��� ����
#include"Stack.h"									//Stack ��� ����
#include"Tree.h"									//Tree ��� ����

template <class T>									//���ø�����
class InorderIterator : public Tree<T>				//Inorderlterator Ŭ���� ����, Tree Ŭ���� ���
{
private:										    //�����������
	Stack<char> s;
	TreeNode<T> *currentNode;
	Tree<char> t;

public:
	InorderIterator()								//�����ڸ� ���� ��� ���� �ʱ�ȭ
	{
		T *Next();									//Next �Լ� ����
		currentNode = root;

	}

	~InorderIterator()
	{

	}

	T *Next()											 //Next �Լ� ����
	{
		while (currentNode)	
		{
			s.Push(currentNode);					     //currentNode�� ���ÿ� ����
			currentNode = currentNode->leftChild;   	 //currentNode �̵�
		}

		if (s.IsEmpty())
			return 0;								     //������ ��������� ����
		currentNode = s.Top();					     	 //currentNode�� ������ �������κ����� ����
		s.Pop();								         //pop�Լ� ȣ��
		t.Visit(currentNode);						     //���� current Node�� ���� �������ҷ� ����� ������ Ȯ���ϱ����Ͽ� visit�Լ� ȣ��
		T &temp = currentNode->s_data;			         //temp�� currentNode�� �ӽ÷� ����
		currentNode = currentNode->rightChild;           //currentNode �̵�
		
		return &temp;								     //&temp ��ȯ
	}
	
};

