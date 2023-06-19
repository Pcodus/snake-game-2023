#include <vector>
#include <iostream>
#include "global.h"
using namespace std;

#ifndef GATE
#define GATE
class Gatepair {
public:
    vector<vector<int>> gate1;
    vector<vector<int>> gate2;
    int dur;
    
    Gatepair(int x1, int y1, int x2, int y2) {
        gate1.push_back({x1, y1});
        gate2.push_back({x2, y2});
        dur = 0;
    }
};

extern vector<Gatepair> gatelist;

void MakeGate(int map[][24][45]);
int PassGate(int map[][24][45], vector<vector<int> >& snake, vector<Gatepair>& usegate, int dir);

#endif