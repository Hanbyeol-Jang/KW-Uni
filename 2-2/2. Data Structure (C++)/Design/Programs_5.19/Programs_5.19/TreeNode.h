#pragma once
#include <iostream>
using namespace std;

template<class T>					//���ø� ����
class TreeNode					    //Ŭ���� ����
{
public:
	T s_data;						//TreeNode ��� ���� ����
	TreeNode<T> *rightChild;
	TreeNode<T> *leftChild;

	TreeNode()
	{
		rightChild = NULL;			//������ ��� NULL�� �ʱ�ȭ
		leftChild = NULL;
	}

	TreeNode(T pair)
	{
		s_data = pair;				//������ ��� NULL�� �ʱ�ȭ
		rightChild = NULL;
		leftChild = NULL;
	}

	~TreeNode()
	{

	}

	T Getdata()						//Getdata �Լ� ����
	{
		return s_data;				//s_data ��ȯ
	}

	void Setdata(T data)			//Setdata �Լ� ����
	{
		s_data = data;				//�Է¹��� data�� s_data�� �Է� 
	}

};