#pragma once
#include "Stack.h"										      //Stack ��� ����

template<class T>                                             //���ø� ����
class Tree : public TreeNode<T>								  //Ŭ���� ���� 
{
public:
	Tree()
	{
		TreeNode<T> *pNode1 = new TreeNode<T>();               //�� 9���� TreeNode�� ����
		TreeNode<T> *pNode2 = new TreeNode<T>();
		TreeNode<T> *pNode3 = new TreeNode<T>();
		TreeNode<T> *pNode4 = new TreeNode<T>();
		TreeNode<T> *pNode5 = new TreeNode<T>();
		TreeNode<T> *pNode6 = new TreeNode<T>();
		TreeNode<T> *pNode7 = new TreeNode<T>();
		TreeNode<T> *pNode8 = new TreeNode<T>();
		TreeNode<T> *pNode9 = new TreeNode<T>();
		root = pNode1;                                        //root �� pNode1�� �ּڰ��־���

		pNode1->leftChild = pNode2;                           //Textbook �׸� 5.16. ó�� ����
		pNode1->rightChild = pNode3;
		pNode2->leftChild = pNode4;
		pNode2->rightChild = pNode5;
		pNode4->leftChild = pNode6;
		pNode4->rightChild = pNode7;
		pNode6->leftChild = pNode8;
		pNode6->rightChild = pNode9;
		  
		pNode1->Setdata('+');                                //Setdata�Լ��� ���� �� Node���� ���� �־���.
		pNode2->Setdata('*');
		pNode3->Setdata('E');
		pNode4->Setdata('*');
		pNode5->Setdata('D');
		pNode6->Setdata('/');
		pNode7->Setdata('C');
		pNode8->Setdata('A');
		pNode9->Setdata('B');

	}

	~Tree()
	{

	}

	void Visit(TreeNode<T> *currentNode)                        //Visit �Լ� ����
	{
		cout << currentNode->Getdata() << " ";                  //currentNode�� data�� ���
	}

	void Inorder()                                              //Inorder �Լ� ����
	{
		Inorder(root);                                          //ó�� Inorder �Լ��� �� ��, �Է¿� root�� �־��ֵ��� ����
	}

	void Inorder(TreeNode<T> *currentNode)                      //����Լ��� ���Ͽ� Inorder��ȸ��� ����
	{
		if (currentNode)
		{
			Inorder(currentNode->leftChild);                    //currentNode�� leftChild�� �Է� ���·��ϴ� Inorder�Լ� ȣ�� 
			Visit(currentNode);                                 //currentNode�� �Է� ���·��ϴ� Visit�Լ� ȣ��
			Inorder(currentNode->rightChild);                   //currentNode�� rightChild�� �Է� ���·��ϴ� Inorder�Լ� ȣ��
		}
	}

	TreeNode *GetRoot()                                         //GetRoot �Լ� ����
	{
		return root;                                            //root ��ȯ
	}
	 
protected:                                                      //root�� protected�� ����
	TreeNode<T> *root;                                          // root ����

};