#pragma once
#include <iostream>
using namespace std;

template<class T>                        //���ø� ����
class TreeNode							 //Ŭ���� ����
{
public:
	T s_data;                            //TreeNode ���� ����
	TreeNode<T> *rightChild;
	TreeNode<T> *leftChild;
	TreeNode<T> *s_Next;
	TreeNode<T> *s_Prev;

public:
	TreeNode()
	{
		s_data = NULL;                   //������ ��� NULL�� �ʱ�ȭ  
		rightChild = NULL;
		leftChild = NULL;
		s_Next = NULL;
		s_Prev = NULL;
	}

	~TreeNode()
	{

	}

	T Getdata()                          //Getdat �Լ� ����
	{
		return s_data;					 //s_data ��ȯ
	}

	void Setdata(T data)                 //Setdata �Լ� ����
	{
		s_data = data;                   //�Է¹��� data�� s_data�� ����
	}

	TreeNode<T> *GetNext()               //GetNext �Լ� ����
	{
		return s_Next;                   //_s_Next ��ȯ
	}

	TreeNode<T> *GetPrev()               //GetPrev �Լ� ����
	{
		return s_Prev;                   //s_Prev ��ȯ
	}

	void SetNext(TreeNode<T> *add)       //SetNext �Լ� ����
	{
		s_Next = add;                    //�Է¹��� add�� s_Next�� ����
	}

	void SetPrev(TreeNode<T> *add)       //SetPrev �Լ� ����
	{
		s_Prev = add;                    //�Է¹��� add�� s_Prev�� ����
	}

};