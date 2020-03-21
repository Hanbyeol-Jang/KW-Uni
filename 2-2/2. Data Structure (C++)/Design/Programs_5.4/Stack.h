#pragma once
#include "TreeNode.h"                 //TreeNode ��� ����

template<class T>                     //���ø� ����
class Stack							  //Ŭ���� ����
{
public:
	Stack()
	{
		s_pHead = NULL;               //���� �ʱ�ȭ
		s_pTail = NULL;
	}

	~Stack()
	{

	}

	void Push(TreeNode<T> *add)       //Push �Լ� ����
	{
		TreeNode<T> *pCur = s_pHead;              //pCur ���� ���� �� Head ������ �ʱ�ȭ
		if (s_pHead == NULL)
			s_pHead = add;                        //ó�� Push �� ��, s_pHead�� ó�� �Է°����� ����

		else
		{
			while (pCur->GetNext() != NULL)       //pCur�� getNext�� Null�� �ƴ� �� ���� ����
			{
				pCur = pCur->GetNext();           //pCur�� ���� ������ Node���� �� �� �ֵ��� ����
			}

			pCur->SetNext(add);                   //���� ���� Stack�� ������ Stack�� ����
			add->SetPrev(pCur);

		}

		s_pTail = add;                            //���� ���� Stack�� Tail�� ����
	}

	void Pop()                                    //Pop �Լ� ����
	{
		TreeNode<T> *temp = s_pTail;              //�ӽ÷� ������ ���� temp ����
		s_pTail = s_pTail->GetPrev();             //tail�� ���� �������� ���� Stack�� �ٷ� �� Stack���� ����

		if (s_pTail != NULL)                      //Tail�� ���� ���� Stack�� �޸𸮸� NULL�� �ʱ�ȭ
			s_pTail->SetNext(NULL);

		if (temp != NULL)                         //�ӽ÷� Tail�� �����ߴ� temp�� NULL�� �ʱ�ȭ
		{
			temp->SetPrev(NULL);
			temp->SetNext(NULL);
		}

		temp = NULL;
	}

	bool IsEmpty()                                //IsEmpty �Լ� ����
	{
		if (s_pHead == NULL)                      //Head�� NULL�̸� 1��ȯ �ƴϸ� 0 ��ȯ
		{
			return 1;
		}

		else
		{
			return 0;
		}
	}

	TreeNode<T> *Top()                            // Top�Լ�����
	{
		if (s_pHead == s_pTail)                   //  ���� Tail �� Head �� ���ٸ� Head�� NULL�� �ʱ�ȭ
			s_pHead = NULL;

		return s_pTail;                           //Tail ��ȯ
	}

private:
	TreeNode<T> *s_pHead;                        //��� ���� ����
	TreeNode<T> *s_pTail;

};