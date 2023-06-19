#include <vector>
#include <iostream>
#include <ncurses.h>
#include "global.h"
#include "map.h"
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

void MakeGate(int map[][24][45]) {
    int x1, y1, x2 , y2;
    do {
        x1 = rand() % 24;
        y1 = rand() % 45;
    } while(map[level][x1][y1] != 1 && map[level][x1][y1] != 7);
    map[level][x1][y1] = 7;
    do {
        x2 = rand() % 24;
        y2 = rand() % 45;
    } while(map[level][x2][y2] != 1 && map[level][x2][y2] != 7);
    map[level][x2][y2] = 7;

    Gatepair gate(x1, y1, x2, y2);
    gatelist.push_back(gate);
}

int PassGate(int map[][24][45], vector<vector<int> >& snake, vector<Gatepair>& usegate, int dir) {
    maintainGate = true;
    for(vector<Gatepair>::iterator it = usegate.begin(); it != usegate.end(); it++) {
        if(it->gate1[0][0] == snake[0][0] && it->gate1[0][1] == snake[0][1]) {
            snake[0][0] = it->gate2[0][0];
            snake[0][1] = it->gate2[0][1];
            break;
        } else if(it->gate2[0][0] == snake[0][0] && it->gate2[0][1] == snake[0][1]) {
            snake[0][0] = it->gate1[0][0];
            snake[0][1] = it->gate1[0][1];
            break;
        }
    }
    int newdir;
    if(snake[0][0] == 0) {
        newdir = KEY_DOWN;
        snake[0][0]++;
    } else if(snake[0][0] == 23) {
        newdir = KEY_UP;
        snake[0][0]--;
    } else if(snake[0][1] == 0) {
        newdir = KEY_RIGHT;
        snake[0][1]++;
    } else if(snake[0][1] == 44) {
        newdir = KEY_LEFT;
        snake[0][1]--;
    } else {
        if(dir == KEY_UP) {
            if(map[level][(snake[0][0]-1)][snake[0][1]] == 1 || map[level][(snake[0][0]-1)][snake[0][1]] == 7) {
                if(map[level][(snake[0][0])][snake[0][1]+1] == 1 || map[level][(snake[0][0])][snake[0][1]+1] == 7) {
                    if(map[level][(snake[0][0])][snake[0][1]-1] == 1 || map[level][(snake[0][0])][snake[0][1]-1] == 7) {
                        snake[0][0]++;
                        newdir = KEY_DOWN;
                    } else {
                        snake[0][1]--;
                        newdir = KEY_LEFT;
                    }
                } else {
                    snake[0][1]++;
                    newdir = KEY_RIGHT;
                }
            } else {
                snake[0][0]--;
                newdir = KEY_UP;
            }
        } else if(dir == KEY_DOWN) {
            if(map[level][(snake[0][0]+1)][snake[0][1]] == 1 || map[level][(snake[0][0])+1][snake[0][1]] == 7) {
                if(map[level][(snake[0][0])][snake[0][1]-1] == 1 || map[level][(snake[0][0])][snake[0][1]-1] == 7) {
                    if(map[level][(snake[0][0])][snake[0][1]+1] == 1 || map[level][(snake[0][0])][snake[0][1]+1] == 7) {
                        snake[0][0]--;
                        newdir = KEY_UP;
                    } else {
                        snake[0][1]++;
                        newdir = KEY_RIGHT;
                    }
                } else {
                    snake[0][1]--;
                    newdir = KEY_LEFT;
                }
            } else {
                snake[0][0]++;
                newdir = KEY_DOWN;
            }
        } else if(dir == KEY_LEFT) {
            if(map[level][(snake[0][0])][snake[0][1]-1] == 1 || map[level][(snake[0][0])][snake[0][1]-1] == 7) {
                if(map[level][(snake[0][0]-1)][snake[0][1]] == 1 || map[level][(snake[0][0]-1)][snake[0][1]] == 7) {
                    if(map[level][(snake[0][0]+1)][snake[0][1]] == 1 || map[level][(snake[0][0]+1)][snake[0][1]] == 7) {
                        snake[0][1]++;
                        newdir = KEY_RIGHT;
                    } else {
                        snake[0][0]++;
                        newdir = KEY_DOWN;
                    }
                } else {
                    snake[0][0]--;
                    newdir = KEY_UP;
                }
            } else {
                snake[0][1]--;
                newdir = KEY_LEFT;
            }
        } else if(dir == KEY_RIGHT) {
            if(map[level][(snake[0][0])][snake[0][1]+1] == 1 || map[level][(snake[0][0])][snake[0][1]+1] == 7) {
                if(map[level][(snake[0][0]+1)][snake[0][0]] == 1 || map[level][(snake[0][0]+1)][snake[0][1]] == 7) {
                    if(map[level][(snake[0][0]-1)][snake[0][1]] == 1 || map[level][(snake[0][0]-1)][snake[0][1]] == 7) {
                        snake[0][1]--;
                        newdir = KEY_LEFT;
                    } else {
                        snake[0][0]--;
                        newdir = KEY_UP;
                    }
                } else {
                    snake[0][0]++;
                    newdir = KEY_DOWN;
                }
            } else {
                snake[0][1]++;
                newdir = KEY_RIGHT;
            }
        }
    }
    cur_dir = newdir;
    return newdir;
}

#endif