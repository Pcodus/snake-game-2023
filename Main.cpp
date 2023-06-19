#include "map.h"
#include "gate.h"
#include "item.h"
#include "move.h"
#include "global.h"
#include <ctime>
#include <cstdlib>
#include <signal.h>
#include <unistd.h>
#include <ncurses.h>
#include <vector>
using namespace std;

#define speed 150000
#define W 100
#define H 30

int level = 0;
int last_dir = 5;
int cur_dir = KEY_RIGHT;
int GamePoint[3] = {0,0,0};
bool maintainGate;
int maintainGate_tick = 0;

bool gameover;
int maxsize = 3;
bool victory[4] = {false,false,false,false};
bool signum = true;

vector<G> growitems;
vector<P> poisonitems;
vector<Gatepair> gatelist;

void GameOver() {
    // GameOverBoard 생성
    WINDOW *gameover = subwin(stdscr, 24, 45, 3, 5); 
    box(gameover, 0, 0);
    attron(COLOR_PAIR(6));
    mvwprintw(gameover, 12, 23, "GAME OVER");
    attroff(COLOR_PAIR(6));
    wrefresh(gameover);
    getch();
    delwin(gameover);
}

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
    WINDOW *board = subwin(stdscr, 24, 45, 3, 5); 
    box(board, 0, 0);
    attron(COLOR_PAIR(2));
    wbkgd(board, COLOR_PAIR(2));
    attroff(COLOR_PAIR(2));
    
    init_pair(3, COLOR_WHITE, COLOR_BLACK);
    init_pair(4, COLOR_BLACK, COLOR_WHITE);
    init_pair(5, COLOR_CYAN, COLOR_CYAN);
    init_pair(6, COLOR_RED, COLOR_BLACK);

    // ScoreBoard 생성
    WINDOW *score = subwin(stdscr, 10, 45, 3, 55); 
    box(score, 0, 0);
    attron(COLOR_PAIR(3));
    wbkgd(score, COLOR_PAIR(3));
    mvwprintw(score, 0, 16, "Score Board");
  
    // MissionBoard 생성
    WINDOW *mission = subwin(stdscr, 12, 45, 15, 55); 
    box(mission, 0, 0);
    attron(COLOR_PAIR(3));
    wbkgd(mission, COLOR_PAIR(3));
    mvwprintw(mission, 0, 15, "Mission Board");
    

    MAP M;
    // make snake Body 
    vector<vector<int>> snake(3);
    snake[0] = {12, 22};
    snake[1] = {12, 21};
    snake[2] = {12, 20};

    M.map[level][snake[0][0]][snake[0][1]] = 3;
    M.map[level][snake[1][0]][snake[1][1]] = 4;
    M.map[level][snake[2][0]][snake[2][1]] = 4;
    
    signal(SIGALRM,sig_alarm);

    gameover = false;
    time_t tmp = time(NULL);  // 현재 시간을 저장
    time_t tmp2 = time(NULL);  // 현재 시간을 저장
    time_t currenttime;
    int itemSig = 5;
    int gateSig = 10;
    int goal_snakeSize=3;
    int goal_growthPoint=1;
    int goal_poisonPoint=0;
    int goal_gatePoint=0;

    while (!gameover) {
        werase(board);
        box(board, 0, 0);
        
        // 맵 초기화
        for(int i = 1; i < 23; i++)
            for(int j = 1; j < 44; j++) {
                if(M.map[level][i][j] != 1)
                    M.map[level][i][j] = 0;
            }

        for(int i = 1; i < 9; i++)
            for(int j = 1; j < 44; j++) {
                mvwprintw(score,i,j, " ");
            }

        for(int i = 1; i < 11; i++)
            for(int j = 1; j < 44; j++) {
               mvwprintw(mission,i,j, " ");
            }

        for (int i = 0; i < growitems.size(); i++)
            M.map[level][growitems[i].x][growitems[i].y] = 5;
        for (int i = 0; i < poisonitems.size(); i++)
            M.map[level][poisonitems[i].x][poisonitems[i].y] = 6;
        
        maxsize = maxsize <= snake.size() ? snake.size() : maxsize;
        // 보드 초기화
        string score_level = "Level : " + to_string(level+1);
        string score_snakeSize = "B : " + to_string(maxsize);
        string score_growthPoint = "+ : " + to_string(GamePoint[0]);
        string score_poisonPoint= "- : " + to_string(GamePoint[1]);
        string score_gatePoint = "G : " + to_string(GamePoint[2]);
        string mission_snakeSize = "B : " + to_string(goal_snakeSize);
        string mission_growthPoint = "+ : " + to_string(goal_growthPoint);
        string mission_poisonPoint= "- : " + to_string(goal_poisonPoint);
        string mission_gatePoint = "G : " + to_string(goal_gatePoint);
        if(goal_snakeSize <= maxsize){
            mission_snakeSize += " (v)";
            victory[0] = true;
        } else mission_snakeSize += " ( )";
        if(goal_growthPoint <= GamePoint[0]){
            mission_growthPoint += " (v)";
            victory[1] = true;
        } else mission_growthPoint += " ( )";
        if(goal_poisonPoint <= GamePoint[1]){
            mission_poisonPoint += " (v)";
            victory[2] = true;
        } else mission_poisonPoint += " ( )";
        if(goal_gatePoint <=  GamePoint[2]){
            mission_gatePoint += " (v)";
            victory[3] = true;
        } else mission_gatePoint += " ( )";

        for (int i = 0; i < gatelist.size(); i++) {
            M.map[level][gatelist[i].gate1[0][0]][gatelist[i].gate1[0][1]] = 7;
            M.map[level][gatelist[i].gate2[0][0]][gatelist[i].gate2[0][1]] = 7;
        }

        M.map[level][snake[0][0]][snake[0][1]] = 3;
        for(int i = 1; i < snake.size(); i++)
            M.map[level][snake[i][0]][snake[i][1]] = 4;

        // 아이템 5초마다 생성
        currenttime = time(NULL);  // 현재 시간을 가져옴
        if (currenttime - tmp >= itemSig) { // 5초가 지나면
            GenerateGrowth(M.map);
            GenerateGrowth(M.map);
            GeneratePoison(M.map);
            GeneratePoison(M.map);
            tmp = currenttime;  // item 생성한 시간 업데이트
        }

        // 5초 지나면 아이템 제거
        for(vector<G>::iterator it = growitems.begin(); it != growitems.end(); it++)
            it->dur++;
        for(vector<P>::iterator it = poisonitems.begin(); it != poisonitems.end(); it++)
            it->dur++;

        for (vector<G>::iterator it = growitems.begin(); it != growitems.end();) {
            if (it->dur == 5000000/speed) {
                M.map[level][it->x][it->y] = 0;
                it = growitems.erase(it);
            } else { ++it; }
        }
        for (vector<P>::iterator it = poisonitems.begin(); it != poisonitems.end();) {
            if (it->dur == 5000000/speed) {
                M.map[level][it->x][it->y] = 0;
                it = poisonitems.erase(it);
            } else { ++it; }
        }

        // Gate 10초마다 생성
        // Gate는 map에 7로 표시
        if (currenttime - tmp2 >= gateSig) { // 10초가 지나면
            MakeGate(M.map);
            tmp2 = currenttime;  // gate 생성한 시간 업데이트
        }

        // 10초 지나면 Gate 제거
        for(vector<Gatepair>::iterator it = gatelist.begin(); it != gatelist.end(); it++)
            it->dur++;

        for (vector<Gatepair>::iterator it = gatelist.begin(); it != gatelist.end();) {
            if (it->dur == 10000000/speed) {
                M.map[level][it->gate1[0][0]][it->gate1[0][1]] = 1;
                M.map[level][it->gate2[0][0]][it->gate2[0][1]] = 1;
                it = gatelist.erase(it);
            } else { ++it; }
        }

        // 초기화 끝

        for(int i = 0; i < 24; i++) {
            for(int j = 0; j < 45; j++) {
                switch (M.map[level][i][j])
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
                    case 7:
                        wattron(board, COLOR_PAIR(5));
                        mvwprintw(board, i, j, " ");
                        wattroff(board, COLOR_PAIR(5));
                        break;
                    default:
                        break;
                }
            }
        }

        mvwprintw(score, 1, 5, score_level.c_str());
        mvwprintw(score, 3, 5, score_snakeSize.c_str());
        mvwprintw(score, 4, 5, score_growthPoint.c_str());
        mvwprintw(score, 5, 5, score_poisonPoint.c_str());
        mvwprintw(score, 6, 5, score_gatePoint.c_str());

        mvwprintw(mission, 3, 5, mission_snakeSize.c_str());
        mvwprintw(mission, 4, 5, mission_growthPoint.c_str());
        mvwprintw(mission, 5, 5, mission_poisonPoint.c_str());
        mvwprintw(mission, 6, 5, mission_gatePoint.c_str());

        wrefresh(board);
        wrefresh(mission);
        wrefresh(score);
        refresh();
        //시간 설정
        signum = true;
        ualarm(speed, 0);
        
        while(signum){
            int input = getch();
            if(input == KEY_UP || input == KEY_DOWN || input == KEY_LEFT || input == KEY_RIGHT)
                cur_dir = input;
        }

        // 패배조건 1. 반대방향 입력
        if(((cur_dir%10) - (last_dir%10) == -1) || ((cur_dir%10) - (last_dir%10) == 1)){
            gameover = true;
        }

        switch (cur_dir)
        {
        case KEY_UP:
            last_dir = MoveUP(M.map, snake, gatelist);
            break;
        case KEY_DOWN:
            last_dir = MoveDOWN(M.map, snake, gatelist);
            break;
        case KEY_LEFT:
            last_dir = MoveLEFT(M.map, snake, gatelist);
            break;
        case KEY_RIGHT:
            last_dir = MoveRIGHT(M.map, snake, gatelist);
            break;
        default:
            last_dir = MoveLAST(M.map, snake, gatelist);
            break;
        }

        if(maintainGate == true)
            maintainGate_tick++;

        if(maintainGate_tick == snake.size()) {
            M.map[level][gatelist.begin()->gate1[0][0]][gatelist.begin()->gate1[0][1]] = 1;
            M.map[level][gatelist.begin()->gate2[0][0]][gatelist.begin()->gate2[0][1]] = 1;
            gatelist.erase(gatelist.begin());
            maintainGate = false;
            maintainGate_tick = 0;
        }

        // 패배 조건
        // 2. 벽에 부딪힘
        // 3. 길이 3 미만
        // 4. 몸에 부딪힘
        if(snake.size() < 3) {
            gameover = true;
        } else if(M.map[level][snake[0][0]][snake[0][1]] == 1) {
            gameover = true;
        } else if(last_dir == 9999) {
            gameover = true;
        }

        // 승리 조건
        if(victory[0] && victory[1] && victory[2] && victory[3]) {
            if(level == 3)
                break;
            snake.erase(snake.begin(),snake.end());
            for (vector<G>::iterator it = growitems.begin(); it != growitems.end();it++)
                M.map[level][it->x][it->y] = 0;
            growitems.erase(growitems.begin(),growitems.end());
            for (vector<P>::iterator it = poisonitems.begin(); it != poisonitems.end();it++)
                M.map[level][it->x][it->y] = 0;
            poisonitems.erase(poisonitems.begin(),poisonitems.end());
            if(gatelist.size()){
                M.map[level][gatelist.begin()->gate1[0][0]][gatelist.begin()->gate1[0][1]] = 1;
                M.map[level][gatelist.begin()->gate2[0][0]][gatelist.begin()->gate2[0][1]] = 1;
                gatelist.erase(gatelist.begin(),gatelist.end());
            }

            snake.push_back({12,22});
            snake.push_back({12,21});
            snake.push_back({12,20});
            cur_dir = KEY_RIGHT; last_dir = 5;
            
            goal_snakeSize=rand()%5 + 2;
            goal_growthPoint=rand()%4 + 2;
            goal_poisonPoint=rand()%3 + 1;
            goal_gatePoint=rand()%3 + 1;
            maxsize = 3;

            GamePoint[0] = 0; GamePoint[1] = 0; GamePoint[2] = 0;
            victory[0] = false; victory[1] = false; victory[2] = false; victory[3] = false;
            level++;
            tmp = currenttime;
            while(currenttime - tmp < 5){
                currenttime = time(NULL);
            }
            tmp2= tmp = currenttime;
        }
    }
    
    WINDOW *gameover_win = newwin(24, 45, 3, 5);
    wbkgd(gameover_win, COLOR_PAIR(6));
    attron(COLOR_PAIR(6));
    if(gameover)
        mvwprintw(gameover_win, 12, 18, "GAME OVER");
    else mvwprintw(gameover_win, 12, 18, "GAME CLEAR!");
    attroff(COLOR_PAIR(6));
    wrefresh(gameover_win);
    refresh();

    wgetch(gameover_win);
    endwin(); // Curses 모드종료
  
    return 0;
}