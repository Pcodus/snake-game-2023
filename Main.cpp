#include <ncurses.h>
#include <vector>
#include "map.h"
#include "snakeMove.cpp"

#define W 100
#define H 30
#define KEY_UP 259
#define KEY_DOWN 258
#define KEY_LEFT 260
#define KEY_RIGHT 261
using namespace std;

int main()
{
    initscr(); // Curses 모드시작
    start_color(); // Color 사용선언
  
    // 전체 윈도우 생성
    WINDOW *back = subwin(stdscr, H, W, 0, 0);
    init_pair(1, COLOR_MAGENTA, COLOR_WHITE); // 색attribute 설정
    box(stdscr, 0, 0); // 윈도우의 경계를 표현한다. 
    attron(COLOR_PAIR(1)); // Attribute 적용
    wbkgd(stdscr, COLOR_PAIR(1));
    attroff(COLOR_PAIR(1));
  
    // SnakeBoard 생성
    init_pair(2, COLOR_BLACK, COLOR_BLACK);
    WINDOW *board = subwin(stdscr, 24, 45, 3, 5 ); 
    box(board, 0, 0);
    attron(COLOR_PAIR(2));
    wbkgd(board, COLOR_PAIR(2));
    attroff(COLOR_PAIR(2));
    
    MAP M;
    init_pair(3, COLOR_WHITE, COLOR_BLUE);
    for(int i = 0; i < 24; i++) {
      for(int j = 0; j < 45; j++) {
          switch (M.map[i][j])
          {
          case 0:
              wattron(board, COLOR_PAIR(2));
              mvwprintw(board, i, j, " ");
              wattron(board, COLOR_PAIR(2));
              break;
          case 1:  // WALL : 파란색
              wattron(board, COLOR_PAIR(3));
              mvwprintw(board, i, j, " ");
              wattron(board, COLOR_PAIR(3));
              break;
          case 2:
              wattron(board, COLOR_PAIR(3));
              mvwprintw(board, i, j, " ");
              wattron(board, COLOR_PAIR(3));
              break;
          default:
              break;
          }
      }
    }

    // ScoreBoard 생성
    WINDOW *score = subwin(stdscr, 10, 45, 3, 55); 
    box(score, 0, 0);
    attron(COLOR_PAIR(2));
    wbkgd(score, COLOR_PAIR(2));
  
    // MissionBoard 생성
    WINDOW *mission = subwin(stdscr, 12, 45, 15, 55); 
    box(mission, 0, 0);
    attron(COLOR_PAIR(2));
    wbkgd(mission, COLOR_PAIR(2));
    

    // make snake Body 
    vector<vector<int>> snake(3);
    snake[0] = {12, 22};
    snake[1] = {12, 21};
    snake[2] = {12, 20};

    int input = getch();
    int state;
    switch (input)
    {
    case KEY_UP:
        state = 1;
        break;
    case KEY_DOWN:
        state = 2; 
        break;
    case KEY_LEFT:
        state = 3; 
        break;
    case KEY_RIGHT:
        state = 4; 
        break;
    default:
        state = 5;
        break;
    }

    if(state == 1){
        MoveUP(M.map, snake);
    }
    else if(state == 2){
        MoveDOWN(M.map, snake);
    }
    else if(state == 3){
        MoveLEFT(M.map, snake);
    }
    else if(state == 4){
        MoveRIGHT(M.map, snake);
    }



    refresh();
    getch(); // 사용자입력대기
    endwin(); // Curses 모드종료
  
    return 0;
}
