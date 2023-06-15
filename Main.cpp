#include <ncurses.h>
#include <vector>
#include "map.h"

#define W 100
#define H 30
using namespace std;

int last_dir;

int MoveUP(int map[][45], vector<vector<int> >& snake) {
    vector<int> tmp;
    vector<int> head = snake[0];

    snake[0][0]--;
    snake[0][0] = snake[0][0] % 24;
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
    snake[0][0] = snake[0][0] % 24;
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
    snake[0][1] = snake[0][1] % 45;
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
    snake[0][1] = snake[0][1] % 45;
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

int main()
{
    initscr(); // Curses 모드시작
    start_color(); // Color 사용선언
    noecho();
    cbreak();
    nodelay(stdscr, true);
    keypad(stdscr, true);
  
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
    
    while (1) {
        werase(board);
        box(board, 0, 0);


        for(int i = 0; i < 24; i++) {
            for(int j = 0; j < 45; j++) {
                switch (M.map[i][j])
                {
                    case 0:
                        wattron(board, COLOR_PAIR(2));
                        mvwprintw(board, i, j, " ");
                        wattroff(board, COLOR_PAIR(2)); // wattron이 아닌 wattroff 사용
                        break;
                    case 1:  // WALL : 검정색
                        wattron(board, COLOR_PAIR(3));
                        mvwprintw(board, i, j, " ");
                        wattroff(board, COLOR_PAIR(3)); // wattron이 아닌 wattroff 사용
                        break;
                    case 2:
                        wattron(board, COLOR_PAIR(3));
                        mvwprintw(board, i, j, " ");
                        wattroff(board, COLOR_PAIR(3)); // wattron이 아닌 wattroff 사용
                        break;
                    case 3:
                        wattron(board, COLOR_PAIR(4));
                        mvwprintw(board, i, j, "H");
                        wattroff(board, COLOR_PAIR(4)); // wattron이 아닌 wattroff 사용
                        break;
                    case 4:
                        wattron(board, COLOR_PAIR(4));
                        mvwprintw(board, i, j, "O");
                        wattroff(board, COLOR_PAIR(4)); // wattron이 아닌 wattroff 사용
                        break;
                    default:
                        break;
                }
            }
        }
        
        int input = getch();
        switch (input)
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

        M.map[snake[0][0]][snake[0][1]] = 3;
        M.map[snake[1][0]][snake[1][1]] = 4;
        M.map[snake[2][0]][snake[2][1]] = 4;
        
        
        // for(int i = 0; i < 24; i++) {
        //     for(int j = 0; j < 45; j++) {
        //         if (M.map[i][j] == 3 || M.map[i][j] == 4) {
        //             M.map[i][j] = 0;
        //         }
        //     }
        // }
        wrefresh(board);
    }

    getch(); // 사용자입력대기
    endwin(); // Curses 모드종료
  
    return 0;
}
