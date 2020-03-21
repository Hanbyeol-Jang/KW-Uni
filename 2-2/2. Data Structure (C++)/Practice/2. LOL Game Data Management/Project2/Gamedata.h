#ifndef _GAMEDATA_H_
#define _GAMEDATA_H_
#pragma once
#include "Characterdata.h"
using namespace std;

class Gamedata {
private:
	int					Gameid;			// game id
	int					Duration;		// game time
	int					Winner;			// winner
	char**				TeamA;		//Red team info
	char**				TeamB;		//Blue team info

public:
	Gamedata() {	
		Gameid = 0;
		Duration = 0;
		Winner = 0;
		TeamA = new char*[5];
		TeamB = new char*[5];
		for (int i = 0; i < 5; i++)
		{
			TeamA[i] = new char[25];
			TeamB[i] = new char[25];
		}
		
	};
	~Gamedata() {};

	void	setGameid(int gid) { Gameid = gid; }
	void	setDuration(int dtime) { Duration = dtime; }
	void	setWinner(int win) { Winner = win; }
	void	setTeamA(char* team_a_name, int order){strcpy(TeamA[order], team_a_name);}
	void	setTeamB(char* team_b_name, int order) { strcpy(TeamB[order], team_b_name); }
	int		getGameid() { return Gameid; }
	int		getDuration() { return Duration; }
	int		getWinner() { return Winner; }
	char**	getTeamA() { return TeamA; }
	char**	getTeamB() { return TeamB; }
};
#endif