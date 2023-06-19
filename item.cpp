#include "item.h"
#include "map.h"
#include "global.h"
#include <ctime>


void GenerateGrowth(int map[][24][45]) {
    int x = rand() % 23 + 1;
    int y = rand() % 44 + 1;
    if (map[level][x][y] != 0) {
        GenerateGrowth(map);
    }
    else {
        G item(x, y);
        growitems.push_back(item);
        map[level][x][y] = 5;
    }
}

void GeneratePoison(int map[][24][45]) {
    int x = rand() % 23 + 1;
    int y = rand() % 44 + 1;
    if (map[level][x][y] != 0) {
       GeneratePoison(map);
    }
    else {
        P item(x, y);
        poisonitems.push_back(item);
        map[level][x][y] = 6;
    }
}