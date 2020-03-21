#pragma once
#include <iostream>
using namespace std;

template<class T>                        //템플릿 선언
class TreeNode							 //클래스 선언
{
public:
	T s_data;                            //TreeNode 변수 선언
	TreeNode<T> *rightChild;
	TreeNode<T> *leftChild;
	TreeNode<T> *s_Next;
	TreeNode<T> *s_Prev;

public:
	TreeNode()
	{
		s_data = NULL;                   //변수를 모두 NULL로 초기화  
		rightChild = NULL;
		leftChild = NULL;
		s_Next = NULL;
		s_Prev = NULL;
	}

	~TreeNode()
	{

	}

	T Getdata()                          //Getdat 함수 선언
	{
		return s_data;					 //s_data 반환
	}

	void Setdata(T data)                 //Setdata 함수 선언
	{
		s_data = data;                   //입력받은 data를 s_data로 변경
	}

	TreeNode<T> *GetNext()               //GetNext 함수 선언
	{
		return s_Next;                   //_s_Next 반환
	}

	TreeNode<T> *GetPrev()               //GetPrev 함수 선언
	{
		return s_Prev;                   //s_Prev 반환
	}

	void SetNext(TreeNode<T> *add)       //SetNext 함수 선언
	{
		s_Next = add;                    //입력받은 add를 s_Next로 변경
	}

	void SetPrev(TreeNode<T> *add)       //SetPrev 함수 선언
	{
		s_Prev = add;                    //입력받은 add를 s_Prev로 변경
	}

};