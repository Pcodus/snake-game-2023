#include <iostream>
#include <ncurses.h>
#include <vector>
#include "gate.h"
#include "global.h"
#include "map.h"
#include "item.h"
using namespace std;

#ifndef MOVE
#define MOVE


int MoveUP(int map[][24][45], vector<vector<int> >& snake, vector<Gatepair>& usegate) {
    vector<int> tmp;
    vector<int> head = snake[0];

    snake[0][0]--;
    if(map[level][snake[0][0]][snake[0][1]] == 5) {
        GamePoint[0]++;
        snake.insert(snake.begin(), {snake[0][0],snake[0][1]});
        snake[1][0]++;
        for(vector<G>::iterator it = growitems.begin(); it != growitems.end(); it++) {
            if(it->x == snake[0][0] && it->y == snake[0][1]){
                growitems.erase(it);
                return KEY_UP;
            }
        }
    }
    else if(map[level][snake[0][0]][snake[0][1]] == 6) {
        GamePoint[1]++;
        snake.pop_back();
        for(int i = 1; i < snake.size(); i++) {
            tmp = snake[i];
            snake[i] = head;
            head = tmp;
        }
        for(vector<P>::iterator it = poisonitems.begin(); it != poisonitems.end(); it++) {
            if(it->x == snake[0][0] && it->y == snake[0][1]){
                poisonitems.erase(it);
                return KEY_UP;
            }
        }
    } else if(map[level][snake[0][0]][snake[0][1]] == 7) {
        GamePoint[2]++;
        int newdir = PassGate(map, snake, usegate, cur_dir);
        for(int i = 1; i < snake.size(); i++) {
            tmp = snake[i];
            snake[i] = head;
            head = tmp;
        }
        return newdir;
    } else if(map[level][snake[0][0]][snake[0][1]] == 4) {
        return 9999;
    }
     for(int i = 1; i < snake.size(); i++) {
        tmp = snake[i];
        snake[i] = head;
        head = tmp;
    }
    return KEY_UP;
}

int MoveDOWN(int map[][24][45], vector<vector<int> >& snake, vector<Gatepair>& usegate) {
    vector<int> tmp;
    vector<int> head = snake[0];

    snake[0][0]++;
    if(map[level][snake[0][0]][snake[0][1]] == 5) {
        GamePoint[0]++;
        snake.insert(snake.begin(), {snake[0][0],snake[0][1]});
        snake[1][0]--;
        for(vector<G>::iterator it = growitems.begin(); it != growitems.end(); it++) {
            if(it->x == snake[0][0] && it->y == snake[0][1]){
                growitems.erase(it);
                for(int i = 1; i < snake.size(); i++) {
                    tmp = snake[i];
                    snake[i] = head;
                    head = tmp;
                }
                return KEY_DOWN;
            }
        }
    } else if(map[level][snake[0][0]][snake[0][1]] == 6) {
        GamePoint[1]++;
        snake.pop_back();
        for(int i = 1; i < snake.size(); i++) {
            tmp = snake[i];
            snake[i] = head;
            head = tmp;
        }
        for(vector<P>::iterator it = poisonitems.begin(); it != poisonitems.end(); it++) {
            if(it->x == snake[0][0] && it->y == snake[0][1]){
                poisonitems.erase(it);
                return KEY_DOWN;
            }
        }
    } else if(map[level][snake[0][0]][snake[0][1]] == 7) {
        GamePoint[2]++;
        int newdir = PassGate(map, snake, usegate, cur_dir);
        for(int i = 1; i < snake.size(); i++) {
            tmp = snake[i];
            snake[i] = head;
            head = tmp;
        }   
        return newdir;
    } else if(map[level][snake[0][0]][snake[0][1]] == 4) {
        return 9999;
    }
    for(int i = 1; i < snake.size(); i++) {
        tmp = snake[i];
        snake[i] = head;
        head = tmp;
    }
    return KEY_DOWN;
}

int MoveLEFT(int map[][24][45], vector<vector<int> >& snake, vector<Gatepair>& usegate) {
    vector<int> tmp;
    vector<int> head = snake[0];

    snake[0][1]--;
    if(map[level][snake[0][0]][snake[0][1]] == 5) {
        GamePoint[0]++;
        snake.insert(snake.begin(), {snake[0][0],snake[0][1]});
        snake[1][1]++;
        for(vector<G>::iterator it = growitems.begin(); it != growitems.end(); it++) {
            if(it->x == snake[0][0] && it->y == snake[0][1]){
                growitems.erase(it);
                return KEY_LEFT;
            }
        }
    } else if(map[level][snake[0][0]][snake[0][1]] == 6) {
        GamePoint[1]++;
        snake.pop_back();
        for(int i = 1; i < snake.size(); i++) {
            tmp = snake[i];
            snake[i] = head;
            head = tmp;
        }
        for(vector<P>::iterator it = poisonitems.begin(); it != poisonitems.end(); it++) {
            if(it->x == snake[0][0] && it->y == snake[0][1]){
                poisonitems.erase(it);       
                return KEY_LEFT;
            }
        }
    } else if(map[level][snake[0][0]][snake[0][1]] == 7) {
        GamePoint[2]++;
        int newdir = PassGate(map, snake, usegate, cur_dir);
        for(int i = 1; i < snake.size(); i++) {
            tmp = snake[i];
            snake[i] = head;
            head = tmp;
        }   
        return newdir;
    } else if(map[level][snake[0][0]][snake[0][1]] == 4) {
        return 9999;
    }
    for(int i = 1; i < snake.size(); i++) {
        tmp = snake[i];
        snake[i] = head;
        head = tmp;
    }
    return KEY_LEFT;
}

int MoveRIGHT(int map[][24][45], vector<vector<int> >& snake, vector<Gatepair>& usegate) {
    vector<int> tmp;
    vector<int> head = snake[0];

    snake[0][1]++;
    if(map[level][snake[0][0]][snake[0][1]] == 5) {
        GamePoint[0]++;
        snake.insert(snake.begin(), {snake[0][0],snake[0][1]});
        snake[1][1]--;
        for(vector<G>::iterator it = growitems.begin(); it != growitems.end(); it++) {
            if(it->x == snake[0][0] && it->y == snake[0][1]){
                growitems.erase(it);
                return KEY_RIGHT;
            }
        }
    } else if(map[level][snake[0][0]][snake[0][1]] == 6) {
        GamePoint[1]++;
        snake.pop_back();
        for(int i = 1; i < snake.size(); i++) {
            tmp = snake[i];
            snake[i] = head;
            head = tmp;
        }
        for(vector<P>::iterator it = poisonitems.begin(); it != poisonitems.end(); it++) {
            if(it->x == snake[0][0] && it->y == snake[0][1]){
                poisonitems.erase(it);       
                return KEY_RIGHT;
            }
        }
    } else if(map[level][snake[0][0]][snake[0][1]] == 7) {
        GamePoint[2]++;
        int newdir = PassGate(map, snake, usegate, cur_dir);
        for(int i = 1; i < snake.size(); i++) {
            tmp = snake[i];
            snake[i] = head;
            head = tmp;
        }
        return newdir;
    } else if(map[level][snake[0][0]][snake[0][1]] == 4) {
        return 9999;
    }
    for(int i = 1; i < snake.size(); i++) {
        tmp = snake[i];
        snake[i] = head;
        head = tmp;
    }   
    return KEY_RIGHT;
}

int MoveLAST(int map[][24][45], vector<vector<int> >& snake, vector<Gatepair>& usegate) {
    switch(snake[0][0] - snake[1][0] + snake[0][1] - snake[1][1]) {
        case 1:
            switch(snake[0][1] - snake[1][1]) {
                case 1:
                    return MoveRIGHT(map,snake, usegate);
                case 0:
                    return MoveDOWN(map,snake, usegate);
            }
        case -1:
            switch(snake[0][1] - snake[1][1]) {
                case -1:
                    return MoveLEFT(map,snake, usegate);
                case 0:
                    return MoveUP(map,snake, usegate);
            }
        default:
            switch(last_dir) {
                case KEY_UP:
                    return MoveUP(map,snake,usegate);
                case KEY_DOWN:
                    return MoveDOWN(map,snake,usegate);
                case KEY_LEFT:
                    return MoveLEFT(map,snake,usegate);
                case KEY_RIGHT:
                    return MoveRIGHT(map,snake,usegate);
            }
    }
    return 0;
}

#endif