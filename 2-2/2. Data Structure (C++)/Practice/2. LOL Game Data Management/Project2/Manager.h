#pragma once
#include "Gamedata.h"
#include "Characterdata.h"
#include "AVLTree.h"
#include "BpTree.h"
using namespace std;
class Manager{
private:
	AVLTree		*avl;	// AVL tree
	BpTree		*bp;		// B+ tree
	ofstream	fout;

public:
	Manager(int bpOrder);//b+ node map size == bpOrder
	~Manager();//memory free only on newly allocated avl and bp

	void	run(const char * command_txt);
	bool	LOAD(char* loadfile);
	//bool	UPDATE(char* updatefile);//Game data change
	bool	SEARCH_GAME(int id1);//AVL TREE search + data save
	bool	SEARCH_CHARACTER(char* Charactername1, char* Charactername2);//B+TREE(boundary search) + data save
	bool	PRINT_GAME();//all game ascending order  + data save
	bool	PRINT_CHARACTER();//input X : all character ascending order + data save
	bool	PRINT_PICK();//max-heap pick descending order(same pick->character name descending order) + data save
	bool	PRINT_WINRATIO();//min-heap ratio ascending order (same pick->character name ascending order) + data save
	void	printErrorCode(int n);
};

