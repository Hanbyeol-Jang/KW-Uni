#pragma once
#include <iostream>
using namespace std;

template<class T>					//템플릿 선언
class TreeNode					    //클래스 선언
{
public:
	T s_data;						//TreeNode 멤버 변수 선언
	TreeNode<T> *rightChild;
	TreeNode<T> *leftChild;

	TreeNode()
	{
		rightChild = NULL;			//변수를 모두 NULL로 초기화
		leftChild = NULL;
	}

	TreeNode(T pair)
	{
		s_data = pair;				//변수를 모두 NULL로 초기화
		rightChild = NULL;
		leftChild = NULL;
	}

	~TreeNode()
	{

	}

	T Getdata()						//Getdata 함수 선언
	{
		return s_data;				//s_data 반환
	}

	void Setdata(T data)			//Setdata 함수 선언
	{
		s_data = data;				//입력받은 data를 s_data에 입력 
	}

};