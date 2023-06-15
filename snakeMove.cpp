#include <iostream>
#include <vector>
using namespace std;

void MoveUP(int map[][45], vector<vector<int>>& snake) {
    vector<int> tmp;
    vector<int> head = snake[0];

    snake[0][0]--;
    for(int i = 1; i < snake.size(); i++) {
        tmp = snake[i];
        snake[i] = head;
        head = tmp;
    }
}

void MoveDOWN(int map[][45], vector<vector<int>>& snake) {
    vector<int> tmp;
    vector<int> head = snake[0];

    snake[0][0]++;
    for(int i = 1; i < snake.size(); i++) {
        tmp = snake[i];
        snake[i] = head;
        head = tmp;
    }
}

void MoveLEFT(int map[][45], vector<vector<int>>& snake) {
    vector<int> tmp;
    vector<int> head = snake[0];

    snake[0][1]--;
    for(int i = 1; i < snake.size(); i++) {
        tmp = snake[i];
        snake[i] = head;
        head = tmp;
    }
}

void MoveRIGHT(int map[][45], vector<vector<int>>& snake) {
    vector<int> tmp;
    vector<int> head = snake[0];

    snake[0][1]++;
    for(int i = 1; i < snake.size(); i++) {
        tmp = snake[i];
        snake[i] = head;
        head = tmp;
    }   
}