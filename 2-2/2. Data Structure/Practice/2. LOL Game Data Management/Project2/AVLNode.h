#ifndef _AVLNODE_H_
#define _AVLNODE_H_

#include "Gamedata.h"

class AVLNode
{
private:
	AVLNode*			pRight;
	AVLNode*			pLeft;
	Gamedata*			pGamedata;
	int					mBF;

public:
	AVLNode(){
		pRight = NULL;
		pLeft = NULL;
		pGamedata = NULL;
		mBF = 0;
	};
	~AVLNode(){};

	void setRight(AVLNode* SN){pRight = SN;}
	void setLeft(AVLNode* SN){pLeft = SN;}
	void setGD(Gamedata* pGame){pGamedata = pGame;}
	void setBF(int a){mBF = a;}
	AVLNode*	getRight(){return pRight;}
	AVLNode*	getLeft(){return pLeft;}
	Gamedata*	getGD(){return pGamedata;}
	int				getBF(){return mBF;}
};

#endif