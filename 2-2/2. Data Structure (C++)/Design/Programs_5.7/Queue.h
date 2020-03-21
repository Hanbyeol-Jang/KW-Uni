#pragma once
#include"TreeNode.h"						 //TreeNode ����� ����

template<class T>							 //���ø� ����
class Queue								     //Ŭ���� ����
{
public:
	Queue()
	{
		s_pHead = NULL;						 //���� �ʱ�ȭ
		s_pTail = NULL;
	}

	~Queue()
	{

	}

	void Push(TreeNode<T> *add)				 //Push �Լ� ����
	{
		TreeNode<T> *pCur = s_pHead;		 //���� ���� ���ÿ� �ʱ�ȭ

		if (s_pHead == NULL)				 //s_pHead�� NULL �̸� s_pHead�� ó�� ���� �Է����� ���� 
			s_pHead = add;

		else								 //�ι�° Push���� ����
		{
			while (pCur->GetNext() != NULL)  //pCur�� GetNext�� NULL�� ������ ����
			{
				pCur = pCur->GetNext();      //pCur�� ����
			}

			pCur->SetNext(add);              //���� ���� ť�� ���� ���������� ���� ť�� ����
			add->SetPrev(pCur);

		}

		s_pTail = add;						 //���� ���������� ���� ���� Tail �� ����
	}

	void Pop()								 //Pop �Լ� ����
	{
		TreeNode<T>* temp = s_pHead;		 //s_pHead�� �� ��° ������ �����ϰ� ����s_pHead�»���
		s_pHead = s_pHead->GetNext();

		temp = NULL;
	}

	bool IsEmpty()						     //IsEmpty �Լ� ����
	{
		if (s_pHead == NULL)				 //s_pHead�� NULL �̶�� 1��ȯ
		{
			return 1;
		}
		else								 //s_pHead�� NULL�� �ƴ϶�� 0��ȯ
		{
			return 0;
		}
	}

	TreeNode<T> *Front()					 //Front �Լ� ����
	{
		return s_pHead;						 //s_pHead ��ȯ
	}

private:
	TreeNode<T>* s_pHead;					 //��� ���� ����
	TreeNode<T>* s_pTail;

};

