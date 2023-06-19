#include <vector>
#include "map.h"
#include "global.h"
#include <iostream>
using namespace std;

#ifndef ITEM
#define ITEM
class G {
public:
    int x;
    int y;
    int dur;
    G(int x, int y) : x(x), y(y) { dur = 0; };
};
class P {
public:
    int x;
    int y;
    int dur;
    P(int x, int y) : x(x), y(y) { dur = 0; };
};

extern vector<G> growitems;
extern vector<P> poisonitems;

void GenerateGrowth(int map[][24][45]);
void GeneratePoison(int map[][24][45]);

#endif