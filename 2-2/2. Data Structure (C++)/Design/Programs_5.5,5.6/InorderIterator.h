#pragma once
#include<iostream>                          
#include"TreeNode.h"								//TreeNode 헤더 참조
#include"Stack.h"									//Stack 헤더 참조
#include"Tree.h"									//Tree 헤더 참조

template <class T>									//템플릿선언
class InorderIterator : public Tree<T>				//Inorderlterator 클래스 선언, Tree 클래스 상속
{
private:										    //멤버변수선언
	Stack<char> s;
	TreeNode<T> *currentNode;
	Tree<char> t;

public:
	InorderIterator()								//생성자를 통해 멤버 변수 초기화
	{
		T *Next();									//Next 함수 생성
		currentNode = root;

	}

	~InorderIterator()
	{

	}

	T *Next()											 //Next 함수 선언
	{
		while (currentNode)	
		{
			s.Push(currentNode);					     //currentNode를 스택에 넣음
			currentNode = currentNode->leftChild;   	 //currentNode 이동
		}

		if (s.IsEmpty())
			return 0;								     //스택이 비어있으면 종료
		currentNode = s.Top();					     	 //currentNode를 스택의 가장윗부분으로 변경
		s.Pop();								         //pop함수 호출
		t.Visit(currentNode);						     //다음 current Node가 다음 중위원소로 제대로 갔는지 확인하기위하여 visit함수 호출
		T &temp = currentNode->s_data;			         //temp에 currentNode값 임시로 저장
		currentNode = currentNode->rightChild;           //currentNode 이동
		
		return &temp;								     //&temp 반환
	}
	
};

