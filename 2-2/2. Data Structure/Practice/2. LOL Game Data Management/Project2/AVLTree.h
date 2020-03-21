#ifndef _AVLTREE_H_
#define _AVLTREE_H_

#include "Gamedata.h"
#include "AVLNode.h"
/* class AVL */

class AVLTree{
private:
	AVLNode*	root;
	ofstream* fout;

public:
	AVLTree(ofstream* fout);
	AVLTree(){
		root=NULL;
	}
	~AVLTree(){};
	bool		Insert(Gamedata* pGame);
	void		Print();
	Gamedata*	Search(int id);
	//-------------------새로 구현한 함수----------------------
	void printGameInfo(Gamedata* pGameData);
	void searchGameInfo(Gamedata* pGameData);

	void AVLTree::setRoot(AVLNode* pGameData);
	AVLNode* AVLTree::getRoot();

};

#endif