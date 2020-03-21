#pragma once
using namespace std;
#include <iostream>
#include <cstring>
#include <fstream>
#include <map>
#include <math.h>
#include <vector>
#include <algorithm>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <functional>
#include <iomanip>
class Characterdata {
private:
	string Cname;//character name
	int Cpick;// character pick
	int Cwin;// character win

public:
	Characterdata() {
		Cname = "";
		Cpick = 0;
		Cwin = 0;
	}
	~Characterdata() {

	}
	//--NODE information in--
	void setname(string in_name)
	{
		Cname = in_name;
	}
	void setpickinc()
	{
		Cpick++;
	}
	void setpickdec() { Cpick--; }
	void setwininc()
	{
		Cwin++;
	}
	void setwindec() { Cwin--; }
	string getname()
	{
		return Cname;
	}
	int getpick() { return Cpick; }
	int getwin() { return Cwin; }
	float getratio() {
		if (Cpick == 0)
			return 0;
		else
			return ((float)Cwin/ (float)Cpick)*100.0; 
	}
};