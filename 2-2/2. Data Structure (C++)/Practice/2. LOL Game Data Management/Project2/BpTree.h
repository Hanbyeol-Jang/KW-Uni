#ifndef _BpTree_H_
#define _BpTree_H_

#include "BpTreeNode.h"
#include "BpTreeDataNode.h"
#include "BpTreeIndexNode.h"
#include "Characterdata.h"
// BpTree

class BpTree{
private:
	BpTreeNode*	root;
	int			order;		// m children
	ofstream*	fout;
public:
	priority_queue<pair<pair<int, string>, Characterdata*>,
			vector<pair<pair<int, string>, Characterdata*> >,
			less<pair<pair<int, string>, Characterdata*> > > pick_heap;

	priority_queue<pair<pair<float, string>, Characterdata*>,
			vector<pair<pair<float, string>, Characterdata*> >,
			greater<pair<pair<float, string>, Characterdata*> > > ratio_heap;
	BpTree(ofstream* fout, int order = 3)
	{
		root = NULL;
		this->order = order;
		this->fout = fout;
	}
	/*BpTree(int order = 3){
		root = NULL;
		this->order = order;
	}*/

	/* essential */
	bool		Insert(Characterdata* new_Character);
	bool		exceedDataNode(BpTreeNode* pDataNode);
	bool		exceedIndexNode(BpTreeNode* pIndexNode);
	void		splitDataNode(BpTreeNode* pDataNode);
	void		splitIndexNode(BpTreeNode* pIndexNode);
	
	void	SearchRange(string start, string end);	// print character range
	BpTreeNode*	searchDataNode(string n);//search character node based on name

	void	Print(); // print all 
	
	void	printCharacterInfo(Characterdata* pCharacter);//print character data
	void	printPickRank();//print pick rank descending order
	void	printRatioRank();//print ratio rank ascending order

	//====================새로 구현한 함수=======================
	void searchCharacterInfo(Characterdata* pCharacter);
	
	void setRoot(BpTreeNode* pGameData)
	{
		root = pGameData;			// root
	}
	BpTreeNode* getRoot()
	{
		return root;
	}
	
};

#endif
