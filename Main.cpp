#include <ncurses.h>
#include <vector>
#include "map.h"
#include "snakeMove.cpp" // Move 함수들 옮겨놓음
#include <ctime> // 의사 난수 생성(게이트, 아이템)
#include <cstdlib>
#include <signal.h>
#include <unistd.h>
#include <iostream>

#define W 100
#define H 30
using namespace std;

int last_dir = 5;
int cur_dir = KEY_RIGHT;
bool gameover;

void GenerateGrowth(int map[][45]) {
    int x = rand() % 23 + 1;
    int y = rand() % 44 + 1;
    if(map[x][y] == 0)
        map[x][y] = 5;  // 5 는 GROWTH ITEM
}

void GeneratePoison(int map[][45]) {
    int x = rand() % 23 + 1;
    int y = rand() % 44 + 1;
    if (map[x][y] == 0)
        map[x][y] = 6;  // 6 은 POISON ITEM
}

void GameOver(WINDOW* board) {
    gameover = true;
    mvwprintw(board, 10, 10, "Game Over!");
    refresh();
}

bool signum = true;
//
void sig_alarm(int sig) {
    signum = false;
}

int main()
{
    initscr(); // Curses 모드시작
    start_color(); // Color 사용선언
    noecho();
    cbreak();
    nodelay(stdscr, true);
    keypad(stdscr, true);
    srand(time(NULL));
  
    // 전체 윈도우 생성
    WINDOW *back = subwin(stdscr, H, W, 0, 0);
    init_pair(1, COLOR_MAGENTA, COLOR_WHITE); // 색attribute 설정
    box(stdscr, 0, 0); // 윈도우의 경계를 표현한다. 
    attron(COLOR_PAIR(1)); // Attribute 적용
    wbkgd(stdscr, COLOR_PAIR(1));
    attroff(COLOR_PAIR(1));
  
    // SnakeBoard 생성
    init_pair(2, COLOR_WHITE, COLOR_WHITE);
    WINDOW *board = subwin(stdscr, 24, 45, 3, 5 ); 
    box(board, 0, 0);
    attron(COLOR_PAIR(2));
    wbkgd(board, COLOR_PAIR(2));
    attroff(COLOR_PAIR(2));
    
    init_pair(3, COLOR_WHITE, COLOR_BLACK);
    init_pair(4, COLOR_BLACK, COLOR_WHITE);
    // ScoreBoard 생성
    WINDOW *score = subwin(stdscr, 10, 45, 3, 55); 
    box(score, 0, 0);
    attron(COLOR_PAIR(3));
    wbkgd(score, COLOR_PAIR(3));
  
    // MissionBoard 생성
    WINDOW *mission = subwin(stdscr, 12, 45, 15, 55); 
    box(mission, 0, 0);
    attron(COLOR_PAIR(3));
    wbkgd(mission, COLOR_PAIR(3));


    MAP M;
    // make snake Body 
    vector<vector<int>> snake(3);
    snake[0] = {12, 22};
    snake[1] = {12, 21};
    snake[2] = {12, 20};

    M.map[snake[0][0]][snake[0][1]] = 3;
    M.map[snake[1][0]][snake[1][1]] = 4;
    M.map[snake[2][0]][snake[2][1]] = 4;
    
    signal(SIGALRM,sig_alarm);

    gameover = false;
    while (!gameover) {
        werase(board);
        box(board, 0, 0);

        
        // 맵 초기화(아이템, 게이트 반영 X)
        for(int i = 1; i < 23; i++)
            for(int j = 1; j < 44; j++)
                M.map[i][j] = 0;

        M.map[snake[0][0]][snake[0][1]] = 3;
        
        for(int i = 1; i < snake.size(); i++)
            M.map[snake[i][0]][snake[i][1]] = 4;
        
        GenerateGrowth(M.map);
        GeneratePoison(M.map);
        // 맵 초기화 끝

        for(int i = 0; i < 24; i++) {
            for(int j = 0; j < 45; j++) {
                switch (M.map[i][j])
                {
                    case 0:
                        wattron(board, COLOR_PAIR(2));
                        mvwprintw(board, i, j, " ");
                        wattroff(board, COLOR_PAIR(2));
                        break;
                    case 1:
                        wattron(board, COLOR_PAIR(3));
                        mvwprintw(board, i, j, " ");
                        wattroff(board, COLOR_PAIR(3));
                        break;
                    case 2:
                        wattron(board, COLOR_PAIR(3));
                        mvwprintw(board, i, j, " ");
                        wattroff(board, COLOR_PAIR(3));
                        break;
                    case 3:
                        wattron(board, COLOR_PAIR(4));
                        mvwprintw(board, i, j, "H");
                        wattroff(board, COLOR_PAIR(4));
                        break;
                    case 4:
                        wattron(board, COLOR_PAIR(4));
                        mvwprintw(board, i, j, "O");
                        wattroff(board, COLOR_PAIR(4));
                        break;
                    case 5:
                        wattron(board, COLOR_PAIR(4));
                        mvwprintw(board, i, j, "G");
                        wattroff(board, COLOR_PAIR(4));
                        break;
                    case 6:
                        wattron(board, COLOR_PAIR(4));
                        mvwprintw(board, i, j, "P");
                        wattroff(board, COLOR_PAIR(4));
                        break;
                    default:
                        break;
                }
            }
        }

        wrefresh(board);
        
        //시간 설정
        signum = true;
        ualarm(100000, 0);
        
        while(signum){
            int input = getch();
            if(input == KEY_UP || input == KEY_DOWN || input == KEY_LEFT || input == KEY_RIGHT)
                cur_dir = input;
        }
        

        // 패배조건 1. 반대방향 입력
        if(((cur_dir%10) - (last_dir%10) == -1) || ((cur_dir%10) - (last_dir%10) == 1)){
            gameover = true;
            break;
        }

        switch (cur_dir)
        {
        case KEY_UP:
            last_dir = MoveUP(M.map, snake);
            break;
        case KEY_DOWN:
            last_dir = MoveDOWN(M.map, snake);
            break;
        case KEY_LEFT:
            last_dir = MoveLEFT(M.map, snake);
            break;
        case KEY_RIGHT:
            last_dir = MoveRIGHT(M.map, snake);
            break;
        default:
            last_dir = MoveLAST(M.map, snake);
            break;
        }

        // 패배 조건
        // 2. 벽에 부딪힘
        // 3. 길이 3 미만
        if(snake.size() < 3) {
            mvwprintw(board, snake[0][0], snake[0][1], "F");
            gameover = true;
            break;    
        } else if(M.map[snake[0][0]][snake[0][1]] == 1) {
            gameover = true;
            break;
        }

    }
    if(gameover == true) {
        // 실패
    } else {
        // 성공
    }

    getch(); // 사용자입력대기
    endwin(); // Curses 모드종료
  
    return 0;
}
