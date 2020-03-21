#include "Manager.h"
Manager::Manager(int bpOrder)
{
	fout.open("log.txt", ios::app); // log textfile open
	avl = new AVLTree(&fout);			// constructor of AVL Tree
	bp = new BpTree(&fout, bpOrder);	// constructor of B+ Tree
}

Manager::~Manager()
{
	delete avl;					// destructor
	delete bp;
	fout.close();
}

void Manager::run(const char* command_txt)
{
	ifstream fin;
	fin.open(command_txt);		// open the file
	int load = -1;

	if (!fin)				// if the file is not open
	{
		cout << "ERROR : 'command_list.txt' was NOT OPEN." << endl;	// print ERROR
		return;				
	}

	char* str = NULL;
	char buf1[256] = {0};
	char buf2[256] = {0};
	
	while (fin.getline(buf1, 128))	// till end of file
	{
		strcpy(buf2, buf1);			// string copy
		str = strtok(buf1, " \n");	// store first token
		bool loadbool;

		if (str == NULL)		// if str don't exist
			continue;

		else if (strcmp(str, "LOAD") == 0)	// when LOAD
		{
			if (load == 1)		// already LOAD
			{
				printErrorCode(100);		// Error
			}
			else if ((str = strtok(NULL, " \n")) == NULL ||(loadbool=LOAD(str))!=true)
			{						// if LOAD function don't exist
				printErrorCode(100);		// Error
			}
			if (loadbool == true)
				load = 1;
		}
		/*
		else if (strcmp(str, "UPDATE")==0)
		{
			if (load != 1)
			{
				printErrorCode(200);
			}// error code 200
			else  if ((strtok(NULL, " \n")) == NULL || !UPDATE(str))
			{
				printErrorCode(200);
			}
		}
		*/
		else if (strcmp(str, "SEARCH_GAME") == 0)	// when SEARCH_GAME
		{
			str = strtok(NULL, " \n");

			if (load != 1)				// if not LOAD
			{
				printErrorCode(100);
			}
			else  if (strtok(NULL, " \n") != NULL || !SEARCH_GAME(atoi(str)))
			{						// if SEARCH_GAME function don't exist
				printErrorCode(300);
			}// error code 300
		}
		else if (strcmp(str, "SEARCH_CHARACTER") == 0)
		{
			char* str1;
			char* Cname1; char* Cname2;

			str = strtok(NULL, "/");		// store first Character 
			str1 = strtok(NULL, "/");		// store second Character
			

			if (str == NULL || str1 == NULL)
			{								// if Characters don't exist
				printErrorCode(400);		// Error
			}
			else if (load != 1)			// if not LOAD
				printErrorCode(100);	// Error
			else
			{
				Cname1 = str;
				Cname2 = str1;

				if ((str = strtok(NULL, " \n")) != NULL || SEARCH_CHARACTER(Cname1, Cname2) != true)
				{								// if SEARCH_CHARCTER function don't exist
					printErrorCode(400);		// Error
				}
			}// error code 400
		}
		else if (strcmp(str, "PRINT_GAME")==0)		// when PRINT_GAME
		{
			if (load != 1)				// if not LOAD
				printErrorCode(100);

			else if ((str = strtok(NULL, " \n")) != NULL || !PRINT_GAME())
			{								// if PRINT_GAME function don't exist
				printErrorCode(500);		// Error
			}// error code 500
		}
		else if (strcmp(str, "PRINT_CHARACTER")==0)		// when PRINT_CHARACTER
		{
			if (load != 1)				// if not LOAD
				printErrorCode(100);	// Error

			else if ((str = strtok(NULL, " \n")) != NULL || !PRINT_CHARACTER())
			{								// if PRINT_CHARACTER function don't exist
				printErrorCode(600);		// Error
			}// error code 600
		}
		else if (strcmp(str, "PRINT_PICK")==0)		// when PRINT_PICK
		{
			if (load != 1)				// if not LOAD
			{
				printErrorCode(100);		// Error
			}
			else if ((str = strtok(NULL, " \n")) != NULL || !PRINT_PICK())
			{								// if PRINT_PICK function don't exist
				printErrorCode(700);			// Error
			}
		}
		else if (strcmp(str, "PRINT_WINRATIO")==0)		// when PRINT_WINRATIO
		{
			if (load != 1)				// if not LOAD
			{
				printErrorCode(100);		// Error
			}
			else if ((str = strtok(NULL, " \n")) != NULL || !PRINT_WINRATIO())
			{								// if PRINT_WINRATIO function don't exist
				printErrorCode(800);		// Error
			}
		}
		else if (strcmp(str, "EXIT")==0)		// when EXIT
		{
			fin.close();			// close the file
			exit(1);				// exit
		}
		fout << endl;
	}
	fin.close();	// close file
}

bool Manager::LOAD(char* loadfile)
{
	ifstream fin;

	fin.open(loadfile);		// open the file
						
	if (!fin)				// if the file is not open
		return false;

	int i = 0;

	while (!fin.eof())					// till end of file
	{
		char Manager[1000] = { 0, };			// array for storing Gamedata informations
		char* token;

		fin.getline(Manager, sizeof(Manager));		// read each lines

		if (i < 1)								// pass first line
		{
			i++;
			continue;
		}

		Gamedata* pGame = new Gamedata();			// dyanamic allocation
		Characterdata* pCharacter = new Characterdata[10];	// dyanamic allocation

		if (strlen(Manager) != 0)
		{
			token = strtok(Manager, "\t");			// cut the line by tab, store it into token
			pGame->setGameid(atoi(token));			// set it Gameid, change char to int
			
			token = strtok(NULL, "\t");				// cut the line by tab, store it into token
			pGame->setDuration(atoi(token));		// set it Duration, change char int

			token = strtok(NULL, "\t");				// cut the line by tab, store it into token
			pGame->setWinner(atoi(token));			// set it Winner, change char int 

			if (atoi(token) == 0)					// when team A win
			{
				for (int i = 0; i < 5; i++)
				{
					token = strtok(NULL, "\t");

					pGame->setTeamA(token, i);		// set every Character each team
					pCharacter[i].setname(token);
					pCharacter[i].setpickinc();		// increase pick
					pCharacter[i].setwininc();		// increase win
				}
				for (int i = 5; i < 10; i++)
				{
					token = strtok(NULL, "\t");

					pGame->setTeamB(token, i-5);	// set every Character each team
					pCharacter[i].setname(token);
					pCharacter[i].setpickinc();		// increase only pick
				}
			}
	
		else if(atoi(token) == 1)						// when team B win
		{
			for (int i = 0; i < 5; i++)
			{
				token = strtok(NULL, "\t");

				pGame->setTeamA(token, i);		// set every Character each team
				pCharacter[i].setname(token);
				pCharacter[i].setpickinc();			// increase only pick
			}
			for (int i = 5; i < 10; i++)
			{
				token = strtok(NULL, "\t");

				pGame->setTeamB(token, i - 5);	// set every Character each team
				pCharacter[i].setname(token);
				pCharacter[i].setpickinc();			// increase pick
				pCharacter[i].setwininc();			// increase win
			}

		}

		avl->Insert(pGame);					// Insert to AVL Tree

		for (int i = 0; i < 10; i++)
		{
			bp->Insert(&pCharacter[i]);			// Insert to B+ Tree
		}
	}
}

fout << "--------------------------------------------------------------------------------" << endl;
fout << "                                      LOAD " << endl;
fout << "--------------------------------------------------------------------------------" << endl;
fout << "game_load.txt" << endl << endl;

return true;//file load complete
}
/*
bool Manager::UPDATE(char* updatefile)
{
	ifstream fin;

	fin.open(updatefile);	
						
	if (!fin)			
		return false;

	fout << "--------------------------------------------------------------------------------" << endl;
	fout << "                                     UPDATE " << endl;
	fout << "--------------------------------------------------------------------------------" << endl;
	fout << "Gameid\t" << "Duration\t" << "Winner\t" << "TeamA_c1\t" << "TeamA_c2\t" << "TeamA_c3\t" << "TeamA_c4\t" << "TeamA_c5\t" <<
		"TeamB_c1\t" << "TeamB_c2\t" << "TeamB_c3\t" << "TeamB_c4\t" << "TeamB_c5\t" << endl;

	int i = 0;

	while (!fin.eof())		
	{
		char Manager[1000] = { 0, };		
		char* token;

		fin.getline(Manager, sizeof(Manager));	

		if (i < 1)						
		{
			i++;
			continue;
		}

		Gamedata* pGame = new Gamedata();	
		Gamedata* pGameUP = new Gamedata();
		Characterdata* pCharacter = new Characterdata[10];
		Characterdata* pCharacterUP = new Characterdata[10];

		if (strlen(Manager) != 0)
		{
			token = strtok(Manager, "\t");			
			pGameUP->setGameid(atoi(token));			

			token = strtok(NULL, "\t");				
			pGameUP->setDuration(atoi(token));		

			token = strtok(NULL, "\t");				
			pGameUP->setWinner(atoi(token));			

			if (atoi(token) == 0)						
			{
				for (int i = 0; i < 5; i++)
				{
					token = strtok(NULL, "\t");

					pGameUP->setTeamA(token, i);
					pCharacterUP[i].setname(token);
					pCharacterUP[i].setpickinc();
					pCharacterUP[i].setwininc();
				}
				for (int i = 5; i < 10; i++)
				{
					token = strtok(NULL, "\t");

					pGameUP->setTeamB(token, i - 5);
					pCharacterUP[i].setname(token);
					pCharacterUP[i].setpickinc();
				}
			}

			else if (atoi(token) == 1)
			{
				for (int i = 0; i < 5; i++)
				{
					token = strtok(NULL, "\t");

					pGameUP->setTeamA(token, i);
					pCharacterUP[i].setname(token);
					pCharacterUP[i].setpickinc();
				}
				for (int i = 5; i < 10; i++)
				{
					token = strtok(NULL, "\t");

					pGameUP->setTeamB(token, i - 5);
					pCharacterUP[i].setname(token);
					pCharacterUP[i].setpickinc();
					pCharacterUP[i].setwininc();
				}
			}
			if (pGameUP->getGameid() == pGame->getGameid())
			{
				pGame->setGameid(pGameUP->getGameid());
				pGame->setDuration(pGameUP->getDuration());
				pGame->setWinner(pGameUP->getWinner());
				for (int i = 0; i < 5; i++)
					pGame->setTeamA[i] = pGameUP->setTeamA[i];
				for (int i = 0; i < 5; i++)
					pGame->setTeamB[i] = pGameUP->setTeamB[i];

				avl->Insert(pGame);

				for (int i = 0; i < 10; i++)
				{
					bp->Insert(&pCharacter[i]);
				}

				fout << pGameUP->getGameid() << "\t" << pGameUP->getDuration() << "\t" << pGameUP->getWinner() <<
					"\t" << pGameUP->getTeamA()[0] << "\t" << pGameUP->getTeamA()[1] << "\t" << pGameUP->getTeamA()[2] <<
					"\t" << pGameUP->getTeamA()[3] << "\t" << pGameUP->getTeamA()[4] << "\t" <<
					pGameUP->getTeamB()[0] << "\t" << pGameUP->getTeamB()[1] << "\t" << pGameUP->getTeamB()[2] << "\t" <<
					pGameUP->getTeamB()[3] << "\t" << pGameUP->getTeamB()[4] << endl;
			}
		}
	}
		return true;//file update complete
}
*/

bool Manager::SEARCH_GAME(int id1)
{
	if (!avl->getRoot())	// check root
		return false;		
	else
	{	
		avl->Search(id1);		// call SEARCH function
		return true;	// game search complete
	}
}

bool Manager::SEARCH_CHARACTER(char* Charactername1, char* Charactername2)
{
	if (!bp->getRoot())		// check root
		return false;
	else
	{
		bp->SearchRange(Charactername1, Charactername2);	// call SEARCH function
		return true;	//character search complete
	}
}

bool Manager::PRINT_GAME()
{
	if (!avl->getRoot())		// check root
		return false;
	else
	{
		avl->Print();	// call PRINT function
		return true;
	}//print Game in gameid ascending order(id	winner	duration	teama	teamb)
}

bool Manager::PRINT_CHARACTER()
{
	if (!bp->getRoot())		// check root
		return false;
	else
	{
		bp->Print();		// call PRINT function
		return true;//charater print complete
	}
}

bool Manager::PRINT_PICK()
{
	if (!bp->getRoot())		// check root
		return false;
	else
	{
		bp->printPickRank();	// call printPickRank function
		return true;//print complete(no print return false)
	}
}

bool Manager::PRINT_WINRATIO()
{
	if (!bp->getRoot())		// chenk root
		return false;
	else
	{
		bp->printRatioRank();	// call printRatioRank function
		return true;//print complete(no print return false)
	}
}

void Manager::printErrorCode(int n)
{
	ofstream fout;
	fout.open("log.txt", ofstream::app);
	fout << "----------------------------------------------------------------------------------------------------------------------" <<endl;
	fout << "                                                        ERROR                                                         " <<endl;
	fout << "----------------------------------------------------------------------------------------------------------------------" <<endl;
	fout << n << endl;
	fout.close();
}
