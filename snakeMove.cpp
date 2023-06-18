#include <iostream>
#include <vector>
#include <ncurses.h>
using namespace std;

int MoveUP(int map[][45], vector<vector<int> >& snake) {
    vector<int> tmp;
    vector<int> head = snake[0];

    snake[0][0]--;
    for(int i = 1; i < snake.size(); i++) {
        tmp = snake[i];
        snake[i] = head;
        head = tmp;
    }
    return KEY_UP;
}

int MoveDOWN(int map[][45], vector<vector<int> >& snake) {
    vector<int> tmp;
    vector<int> head = snake[0];

    snake[0][0]++;
    for(int i = 1; i < snake.size(); i++) {
        tmp = snake[i];
        snake[i] = head;
        head = tmp;
    }
    return KEY_DOWN;
}

int MoveLEFT(int map[][45], vector<vector<int> >& snake) {
    vector<int> tmp;
    vector<int> head = snake[0];

    snake[0][1]--;
    for(int i = 1; i < snake.size(); i++) {
        tmp = snake[i];
        snake[i] = head;
        head = tmp;
    }
    return KEY_LEFT;
}

int MoveRIGHT(int map[][45], vector<vector<int> >& snake) {
    vector<int> tmp;
    vector<int> head = snake[0];

    snake[0][1]++;
    for(int i = 1; i < snake.size(); i++) {
        tmp = snake[i];
        snake[i] = head;
        head = tmp;
    }   
    return KEY_RIGHT;
}

int MoveLAST(int map[][45], vector<vector<int> >& snake) {
    switch(snake[0][0] - snake[1][0]) {
        case 1:
            return MoveDOWN(map,snake);
        case -1:
            return MoveUP(map,snake);
        case 0:
            switch(snake[0][1] - snake[1][1]) {
                case 1:
                    return MoveRIGHT(map,snake);
                case -1:
                    return MoveLEFT(map,snake);
            }
    }
    return 0;
}
