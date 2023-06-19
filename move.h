#include <vector>
#include "gate.h"
#include "global.h"
#include <iostream>
using namespace std;

#ifndef MOVE
#define MOVE

int MoveUP(int map[][24][45], vector<vector<int> >& snake, vector<Gatepair>& usegate);
int MoveDOWN(int map[][24][45], vector<vector<int> >& snake, vector<Gatepair>& usegate);
int MoveLEFT(int map[][24][45], vector<vector<int> >& snake, vector<Gatepair>& usegate);
int MoveRIGHT(int map[][24][45], vector<vector<int> >& snake, vector<Gatepair>& usegate);
int MoveLAST(int map[][24][45], vector<vector<int> >& snake, vector<Gatepair>& usegate);

#endif