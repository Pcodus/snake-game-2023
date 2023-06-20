#include <vector>
#include "map.h"
#include "global.h"
#include <iostream>
#include <ctime>
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

void GenerateGrowth(int map[][24][45]) {
    int x,y;
    do {
    x = rand() % 23 + 1;
    y = rand() % 44 + 1;
    } while(map[level][x][y] > 0);

    G item(x, y);
    growitems.push_back(item);
    map[level][x][y] = 5;
}

void GeneratePoison(int map[][24][45]) {
    int x,y;
    do {
    x = rand() % 23 + 1;
    y = rand() % 44 + 1;
    } while(map[level][x][y] > 0);

    P item(x, y);
    poisonitems.push_back(item);
    map[level][x][y] = 6;
}


#endif
