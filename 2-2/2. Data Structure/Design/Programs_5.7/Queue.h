#pragma once
#include"TreeNode.h"						 //TreeNode 헤더를 참조

template<class T>							 //템플릿 선언
class Queue								     //클래스 선언
{
public:
	Queue()
	{
		s_pHead = NULL;						 //변수 초기화
		s_pTail = NULL;
	}

	~Queue()
	{

	}

	void Push(TreeNode<T> *add)				 //Push 함수 선언
	{
		TreeNode<T> *pCur = s_pHead;		 //변수 선언 동시에 초기화

		if (s_pHead == NULL)				 //s_pHead가 NULL 이면 s_pHead를 처음 받은 입력으로 설정 
			s_pHead = add;

		else								 //두번째 Push부터 들어옴
		{
			while (pCur->GetNext() != NULL)  //pCur의 GetNext가 NULL일 때까지 진행
			{
				pCur = pCur->GetNext();      //pCur값 변경
			}

			pCur->SetNext(add);              //새로 들어온 큐를 가장 마지막으로 들어온 큐랑 연결
			add->SetPrev(pCur);

		}

		s_pTail = add;						 //가장 마지막으로 들어온 값을 Tail 로 설정
	}

	void Pop()								 //Pop 함수 선언
	{
		TreeNode<T>* temp = s_pHead;		 //s_pHead을 두 번째 값으로 변경하고 원래s_pHead는삭제
		s_pHead = s_pHead->GetNext();

		temp = NULL;
	}

	bool IsEmpty()						     //IsEmpty 함수 선언
	{
		if (s_pHead == NULL)				 //s_pHead가 NULL 이라면 1반환
		{
			return 1;
		}
		else								 //s_pHead가 NULL이 아니라면 0반환
		{
			return 0;
		}
	}

	TreeNode<T> *Front()					 //Front 함수 선언
	{
		return s_pHead;						 //s_pHead 반환
	}

private:
	TreeNode<T>* s_pHead;					 //멤버 변수 선언
	TreeNode<T>* s_pTail;

};

