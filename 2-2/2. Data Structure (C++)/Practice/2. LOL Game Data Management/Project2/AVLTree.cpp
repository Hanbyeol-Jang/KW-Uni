#include "AVLTree.h"
bool AVLTree::Insert(Gamedata* pGame)
{
	if (pGame == NULL)
		return false;

	AVLNode* pNew = new AVLNode;	//make a new AvlNode
	pNew->setGD(pGame);				//store gamedata in Node

	if (root == NULL)				//If it is first in node
	{
		root = pNew;
		return true;
	}

	//Locate insertion point for e
	//a = most recent node with bf = +-1
	//pa = parent of a
	//p = p moves through the tree
	//pp = parent of p
	AVLNode *a = root, *pa = NULL, *p = root, *pp = NULL, *rootSub = NULL;

	while (p != NULL)	//search insert to location and standard
	{
		if (p->getBF() != 0)
		{
			a = p;
			pa = pp;
		}	//Find turned criteria
		if (p->getGD()->getGameid()<pNew->getGD()->getGameid())	//if new node name is bigger than name of p pointer 
		{
			pp = p;
			p = p->getRight();
		}	//move p, and set pp
		else			//if new node name is smaller than name of p pointer
		{
			pp = p; p = p->getLeft();
		}	//move to left
	}
	//insert and rebalance
	if (pNew->getGD()->getGameid()> pp->getGD()->getGameid())	//if new node name is bigger than name of pp pointer
		pp->setRight(pNew);		//set right of pp
	else
		pp->setLeft(pNew);

	//adjust balance factor of nodes on path from a to pp	
	int d;					//it is rotation
	AVLNode * b, *c;		//b is child of a, c is child of b

	if (pNew->getGD()->getGameid()> a->getGD()->getGameid())	//if new node go to right 
	{
		b = p = a->getRight();
		d = -1;		//it is bf
	}
	else			//if node is go to left
	{
		b = p = a->getLeft();
		d = 1;		//if if bf
	}

	while (p != pNew)
	{
		if (pNew->getGD()->getGameid()> p->getGD()->getGameid())
		{
			p->setBF(-1);
			p = p->getRight();		//height of right increases by 1
		}
		else			//height of left increase by 1
		{
			p->setBF(1);
			p = p->getLeft();
		}
	}

	if (a->getBF() == 0 || a->getBF() + d == 0)//is AVLtree unbalanced?
	{	//it is balanced tree
		a->setBF(a->getBF() + d);
		return true;
	}

	if (d == 1)	//tree unbalanced, determine rotation type
	{	//left imbalance
		if (b->getBF() == 1)
		{	//rototion type LL
			a->setLeft(b->getRight());
			b->setRight(a); a->setBF(0); b->setBF(0);
			rootSub = b;	//b is the new root of the subtree
		}
		else
		{	//rotation type LR
			c = b->getRight();
			b->setRight(c->getLeft());
			a->setLeft(c->getRight());
			c->setLeft(b);
			c->setRight(a);
			switch (c->getBF())
			{
			case 0:
				b->setBF(0); a->setBF(0);
				break;
			case 1:
				b->setBF(0); a->setBF(-1);
				break;
			case -1:
				b->setBF(1); a->setBF(0);
				break;
			}
			c->setBF(0); rootSub = c;	 //c is the new root of the subtree
		}	//end of LR
	}	//end of left imbalance

	else {	//right imbalance
		if (b->getBF() == -1)
		{	//rototion type RR
			a->setRight(b->getLeft());
			b->setLeft(a); a->setBF(0); b->setBF(0);
			rootSub = b;	//b is the new root of the subtree
		}
		else
		{	//rotation type RL
			c = b->getLeft();
			b->setLeft(c->getRight());
			a->setRight(c->getLeft());
			c->setRight(b);
			c->setLeft(a);
			switch (c->getBF())
			{
			case 0:
				b->setBF(0); a->setBF(0);
				break;
			case 1:
				b->setBF(-1); a->setBF(0);
				break;
			case -1:
				b->setBF(0); a->setBF(1);
				break;
			}
			c->setBF(0); rootSub = c;	//c is the new root of the subtree
		}	//end of LR
	}	//end of right imbalance
	 //subtree with root b has been rebalanced
	if (pa == NULL)
		root = rootSub;
	else if (a == pa->getLeft())
		pa->setLeft(rootSub);
	else
		pa->setRight(rootSub);

	return true;	// no duplication
}

void AVLTree::Print()
{
	stack<AVLNode*> s;				// for ascending
	AVLNode* currentNode = root;	// visit root first

	if (currentNode == NULL)		// if root don't exist
		return;

	*fout << "--------------------------------------------------------------------------------" << endl;
	*fout << "                                   PRINT GAME " << endl;
	*fout << "--------------------------------------------------------------------------------" << endl;
	*fout << "Gameid\t" << "Duration\t" << "Winner\t" <<
		"TeamA_c1\t" << "TeamA_c2\t" << "TeamA_c3\t" << "TeamA_c4\t" << "TeamA_c5\t" <<
		"TeamB_c1\t" << "TeamB_c2\t" << "TeamB_c3\t" << "TeamB_c4\t" << "TeamB_c5\t" << endl;
	
	while (1)					// check ascending of Gameid 
	{
		while (currentNode)
		{
			s.push(currentNode);			// pust into stack
			currentNode = currentNode->getLeft();	//	move to left
		}
		if (s.empty())			// is it empty?
			break;				// if yes, break
		currentNode = s.top();		// top of stack
		s.pop();					// pop from stack
		printGameInfo(currentNode->getGD());	// call function for print form
		currentNode = currentNode->getRight();	// move to right
	}
}

Gamedata* AVLTree::Search(int id)
{
	AVLNode* pCur = root;		//pCur is AVL Tree root

	if (pCur == NULL || id == NULL)	// if pCur don't exist
		return false;

	while (pCur->getGD()->getGameid()!= id)		
	{
		if (pCur->getGD()->getGameid()> id)	// if new id is less than pCur's id
			pCur = pCur->getLeft();		//	move to left
		else							// or
			pCur = pCur->getRight();	// move to right

		if (!pCur->getLeft() && !pCur->getRight() && pCur->getGD()->getGameid()!=id)	// at last
			return false;
	}

	Gamedata* pGD = pCur->getGD();

	*fout << "--------------------------------------------------------------------------------" << endl;
	*fout << "                                     SEARCH " << id << endl;
	*fout << "--------------------------------------------------------------------------------" << endl;
	searchGameInfo(pGD);		// call function for print form

	return NULL;
}

void AVLTree::printGameInfo(Gamedata* pGameData)		//	print form of GameInfo	when PRINT
{
	*fout << pGameData->getGameid() << "\t" << pGameData->getDuration() << "\t" << pGameData->getWinner() <<
		"\t" << pGameData->getTeamA()[0] << "\t" << pGameData->getTeamA()[1] << "\t" << pGameData->getTeamA()[2] <<
		"\t" << pGameData->getTeamA()[3] << "\t" << pGameData->getTeamA()[4] << "\t" <<
		pGameData->getTeamB()[0] << "\t" << pGameData->getTeamB()[1] << "\t" << pGameData->getTeamB()[2] << "\t" <<
		pGameData->getTeamB()[3] << "\t" << pGameData->getTeamB()[4] << endl;
}
void AVLTree::searchGameInfo(Gamedata* pGameData)		// print form of Gameinfo when SEARCH
{
	*fout << "Gameid : " << pGameData->getGameid() << endl;
	*fout << "Duration : " << pGameData->getDuration() << endl;
	*fout << "Winner : " << pGameData->getWinner() << endl;
	*fout << "TeamA : " << pGameData->getTeamA()[0] << "/" << pGameData->getTeamA()[1] << "/" <<
		pGameData->getTeamA()[2] << "/" << pGameData->getTeamA()[3] << "/" << pGameData->getTeamA()[4] << endl;
	*fout << "TeamB : " << pGameData->getTeamB()[0] << "/" << pGameData->getTeamB()[1] << "/" <<
		pGameData->getTeamB()[2] << "/" << pGameData->getTeamB()[3] << "/" << pGameData->getTeamB()[4] << endl;
}

void AVLTree::setRoot(AVLNode* pGameData)		// set root
{
	root = pGameData;		
}
AVLNode* AVLTree::getRoot()				// get root
{
	return root;
}

AVLTree::AVLTree(ofstream* fout)	// constructor
{
	this->fout = fout;
}