#pragma once
#include "TreeNode.h"                 //TreeNode 헤더 참조

template<class T>                     //템플릿 선언
class Stack							  //클래스 선언
{
public:
	Stack()
	{
		s_pHead = NULL;               //변수 초기화
		s_pTail = NULL;
	}

	~Stack()
	{

	}

	void Push(TreeNode<T> *add)       //Push 함수 선언
	{
		TreeNode<T> *pCur = s_pHead;              //pCur 변수 선언 후 Head 값으로 초기화
		if (s_pHead == NULL)
			s_pHead = add;                        //처음 Push 할 때, s_pHead를 처음 입력값으로 설정

		else
		{
			while (pCur->GetNext() != NULL)       //pCur의 getNext가 Null이 아닐 때 까지 진행
			{
				pCur = pCur->GetNext();           //pCur을 가장 마지막 Node까지 갈 수 있도록 변경
			}

			pCur->SetNext(add);                   //새로 들어온 Stack을 마지막 Stack과 연결
			add->SetPrev(pCur);

		}

		s_pTail = add;                            //새로 들어온 Stack을 Tail로 지정
	}

	void Pop()                                    //Pop 함수 선언
	{
		TreeNode<T> *temp = s_pTail;              //임시로 저장할 변수 temp 선언
		s_pTail = s_pTail->GetPrev();             //tail을 가장 마지막에 들어온 Stack의 바로 전 Stack으로 변경

		if (s_pTail != NULL)                      //Tail의 다음 들어올 Stack의 메모리를 NULL로 초기화
			s_pTail->SetNext(NULL);

		if (temp != NULL)                         //임시로 Tail을 저장했던 temp를 NULL로 초기화
		{
			temp->SetPrev(NULL);
			temp->SetNext(NULL);
		}

		temp = NULL;
	}

	bool IsEmpty()                                //IsEmpty 함수 선언
	{
		if (s_pHead == NULL)                      //Head가 NULL이면 1반환 아니면 0 반환
		{
			return 1;
		}

		else
		{
			return 0;
		}
	}

	TreeNode<T> *Top()                            // Top함수선언
	{
		if (s_pHead == s_pTail)                   //  만약 Tail 과 Head 가 같다면 Head를 NULL로 초기화
			s_pHead = NULL;

		return s_pTail;                           //Tail 반환
	}

private:
	TreeNode<T> *s_pHead;                        //멤버 변수 선언
	TreeNode<T> *s_pTail;

};