#include <iostream>
#include <vector>
#include <ncurses.h>
#include "item.h"
using namespace std;

#ifndef MOVE
#define MOVE

// int MoveUP(int map[][45], vector<vector<int> >& snake) {
//     vector<int> tmp;
//     vector<int> head = snake[0];

//     snake[0][0]--;
//     // growth, poison, hit body
//     if(map[snake[0][0]][snake[0][1]] == 5) {
//         snake.insert(snake.begin(), {snake[0][0],snake[0][1]});
//         snake[0][0]++;
//         // 이 좌표의 아이템 벡터를 찾아야댐
//         for(vector<G>::iterator it = growitems.begin(); it != growitems.end(); it++)
//             if(it->x == snake[0][0] && it->y == snake[0][1]){
//                 growitems.erase(it);
//             }
//         // 그리고 그 아이템 벡터 삭제
//         return KEY_UP;
//     } 
//     else if(map[snake[0][0]][snake[0][1]] == 6) {
//         snake.pop_back();
//         for(vector<G>::iterator it = poisonitems.begin(); it != poisonitems.end(); it++)
//             if(it->x == snake[0][0] && it->y == snake[0][1]){
//                 poisonitems.erase(it);
//             }
//         return KEY_UP;
//     }
//     else if(map[snake[0][0]][snake[0][1]] == 4) {
//         return 9999;
//     }
//     for(int i = 1; i < snake.size(); i++) {
//         tmp = snake[i];
//         snake[i] = head;
//         head = tmp;
//     }
//     return KEY_UP;
// }

// int MoveDOWN(int map[][45], vector<vector<int> >& snake) {
//     vector<int> tmp;
//     vector<int> head = snake[0];

//     snake[0][0]++;
//     if(map[snake[0][0]][snake[0][1]] == 5) {
//         snake.insert(snake.begin(), {snake[0][0],snake[0][1]});
//         snake[0][0]--;
//         for(vector<G>::iterator it = growitems.begin(); it != growitems.end(); it++)
//             if(it->x == snake[0][0] && it->y == snake[0][1]){
//                 growitems.erase(it);
//             }
//         return KEY_DOWN;
//     } else if(map[snake[0][0]][snake[0][1]] == 6) {
//         snake.pop_back();
//         for(vector<G>::iterator it = poisonitems.begin(); it != poisonitems.end(); it++)
//             if(it->x == snake[0][0] && it->y == snake[0][1]){
//                 poisonitems.erase(it);
//             }
//         return KEY_UP;
//     } 
//     else if(map[snake[0][0]][snake[0][1]] == 4) {
//         return 9999;
//     }
//     for(int i = 1; i < snake.size(); i++) {
//         tmp = snake[i];
//         snake[i] = head;
//         head = tmp;
//     }
//     return KEY_DOWN;
// }

// int MoveLEFT(int map[][45], vector<vector<int> >& snake) {
//     vector<int> tmp;
//     vector<int> head = snake[0];

//     snake[0][1]--;
//     if(map[snake[0][0]][snake[0][1]] == 5) {
//         snake.insert(snake.begin(), {snake[0][0],snake[0][1]});
//         snake[0][1]++;
//         for(vector<G>::iterator it = growitems.begin(); it != growitems.end(); it++)
//             if(it->x == snake[0][0] && it->y == snake[0][1]){
//                 growitems.erase(it);
//             }
//         return KEY_LEFT;
//     } else if(map[snake[0][0]][snake[0][1]] == 6) {
//         snake.pop_back();
//         for(vector<G>::iterator it = poisonitems.begin(); it != poisonitems.end(); it++)
//             if(it->x == snake[0][0] && it->y == snake[0][1]){
//                 poisonitems.erase(it);
//             }
//         return KEY_UP;
//     } 
//     else if(map[snake[0][0]][snake[0][1]] == 4) {
//         return 9999;
//     }
//     for(int i = 1; i < snake.size(); i++) {
//         tmp = snake[i];
//         snake[i] = head;
//         head = tmp;
//     }
//     return KEY_LEFT;
// }

// int MoveRIGHT(int map[][45], vector<vector<int> >& snake) {
//     vector<int> tmp;
//     vector<int> head = snake[0];

//     snake[0][1]++;
//     if(map[snake[0][0]][snake[0][1]] == 5) {
//         snake.insert(snake.begin(), {snake[0][0],snake[0][1]});
//         snake[0][1]--;
//         for(vector<G>::iterator it = growitems.begin(); it != growitems.end(); it++)
//             if(it->x == snake[0][0] && it->y == snake[0][1]){
//                 growitems.erase(it);
//             }
//         return KEY_RIGHT;
//     } else if(map[snake[0][0]][snake[0][1]] == 6) {
//         snake.pop_back();
//         for(vector<G>::iterator it = poisonitems.begin(); it != poisonitems.end(); it++)
//             if(it->x == snake[0][0] && it->y == snake[0][1]){
//                 poisonitems.erase(it);
//             }
//         return KEY_UP;
//     }
//     else if(map[snake[0][0]][snake[0][1]] == 4) {
//         return 9999;
//     }
//     for(int i = 1; i < snake.size(); i++) {
//         tmp = snake[i];
//         snake[i] = head;
//         head = tmp;
//     }   
//     return KEY_RIGHT;
// }

// int MoveLAST(int map[][45], vector<vector<int> >& snake) {
//     switch(snake[0][0] - snake[1][0]) {
//         case 1:
//             return MoveDOWN(map,snake);
//         case -1:
//             return MoveUP(map,snake);
//         case 0:
//             switch(snake[0][1] - snake[1][1]) {
//                 case 1:
//                     return MoveRIGHT(map,snake);
//                 case -1:
//                     return MoveLEFT(map,snake);
//             }
//     }
//     return 0;
// }

#endif