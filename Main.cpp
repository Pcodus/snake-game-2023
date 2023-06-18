#include <ncurses.h>
#include <vector>
#include "map.h"
#include "gate.h"
#include <ctime>
#include <cstdlib>
#include <signal.h>
#include <unistd.h>
#include <iostream>

#define speed 150000
#define W 100
#define H 30
using namespace std;

int last_dir = 5;
int cur_dir = KEY_RIGHT;
bool gameover;
int maxsize = 3;
int level = 0;
bool victory[4] = {false,false,false,false};

class G {
public:
    int x;
    int y;
    int dur;
    G(int x, int y) : x(x), y(y) { dur = 0; };
};
class P {
public:
    int x;
    int y;
    int dur;
    P(int x, int y) : x(x), y(y) { dur = 0; };
};

vector<G> growitems;
vector<P> poisonitems;
int GamePoint[3] = {0,0,0};
vector<Gatepair> gatelist;


int MoveUP(int map[][24][45], vector<vector<int> >& snake) {
    vector<int> tmp;
    vector<int> head = snake[0];

    snake[0][0]--;
    // growth, poison, hit body
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
    }
    else if(map[level][snake[0][0]][snake[0][1]] == 4) {
        return 9999;
    }
    for(int i = 1; i < snake.size(); i++) {
        tmp = snake[i];
        snake[i] = head;
        head = tmp;
    }
    return KEY_UP;
}

int MoveDOWN(int map[][24][45], vector<vector<int> >& snake) {
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
    } 
    else if(map[level][snake[0][0]][snake[0][1]] == 4) {
        return 9999;
    }
    for(int i = 1; i < snake.size(); i++) {
        tmp = snake[i];
        snake[i] = head;
        head = tmp;
    }
    return KEY_DOWN;
}

int MoveLEFT(int map[][24][45], vector<vector<int> >& snake) {
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
    } 
    else if(map[level][snake[0][0]][snake[0][1]] == 4) {
        return 9999;
    }
    for(int i = 1; i < snake.size(); i++) {
        tmp = snake[i];
        snake[i] = head;
        head = tmp;
    }
    return KEY_LEFT;
}

int MoveRIGHT(int map[][24][45], vector<vector<int> >& snake) {
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
    }
    else if(map[level][snake[0][0]][snake[0][1]] == 4) {
        return 9999;
    }
    for(int i = 1; i < snake.size(); i++) {
        tmp = snake[i];
        snake[i] = head;
        head = tmp;
    }   
    return KEY_RIGHT;
}

int MoveLAST(int map[][24][45], vector<vector<int> >& snake) {
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

void MakeGate(int map[][24][45]) {
    int x1 = rand() % 23 + 1;
    int y1 = rand() % 44 + 1;
    while( !(map[level][x1][y1] == 1) ) {
        x1 = rand() % 23 + 1;
        y1 = rand() % 44 + 1;
    }
    int x2 = rand() % 23 + 1;
    int y2 = rand() % 44 + 1;
    while( !(map[level][x2][y2] == 1) ) {
        x2 = rand() % 23 + 1;
        y2 = rand() % 44 + 1;
    }
    Gatepair gate(x1, y1, x2, y2);
    gatelist.push_back(gate);
    map[level][x1][y1] = map[level][x2][y2] = 7;
}

void GameOver(WINDOW* board) {
    gameover = true;
    mvwprintw(board, 10, 10, "Game Over!");
    refresh();
}

bool signum = true;
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
    // ScoreBoard 생성
    WINDOW *score = subwin(stdscr, 10, 45, 3, 55); 
    box(score, 0, 0);
    attron(COLOR_PAIR(3));
    wbkgd(score, COLOR_PAIR(3));
    mvwprintw(score, 0, 14, "Score Board");
  
    // MissionBoard 생성
    WINDOW *mission = subwin(stdscr, 12, 45, 15, 55); 
    box(mission, 0, 0);
    attron(COLOR_PAIR(3));
    wbkgd(mission, COLOR_PAIR(3));
    mvwprintw(mission, 0, 14, "Mission Board");

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

    int goal_snakeSize=rand()%5 + 5;
    int goal_growthPoint=rand()%5 + 5;
    int goal_poisonPoint=rand()%3 + 5;
    int goal_gatePoint=rand()%3 ;

    int gateSig = 10;
    // MapLevel(M.map[level],level);

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

    while (!gameover) {
        werase(board);
        box(board, 0, 0);
        
        // 맵 초기화
        for(int i = 1; i < 23; i++)
            for(int j = 1; j < 44; j++) {
                if(M.map[level][i][j] != 1 && M.map[level][i][j] != 7)
                    M.map[level][i][j] = 0;
            }

        for (int i = 0; i < growitems.size(); i++)
            M.map[level][growitems[i].x][growitems[i].y] = 5;
        for (int i = 0; i < poisonitems.size(); i++)
            M.map[level][poisonitems[i].x][poisonitems[i].y] = 6;
        
        maxsize = maxsize <= snake.size() ? snake.size() : maxsize;
        // 보드 초기화
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
            M.map[level][gatelist[i].gate1[0].first][gatelist[i].gate1[0].second] = 7;
            M.map[level][gatelist[i].gate2[0].first][gatelist[i].gate2[0].second] = 7;
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
                M.map[level][it->gate1[0].first][it->gate1[0].second] = 1;
                M.map[level][it->gate2[0].first][it->gate2[0].second] = 1;
                it = gatelist.erase(it);
            } else { ++it; }
        }

        // 맵 초기화 끝

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

        mvwprintw(score, 1, 5, to_string(level + 1).c_str());
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
        // 4. 몸에 부딪힘
        if(snake.size() < 3) {
            gameover = true;
            break;    
        } else if(M.map[level][snake[0][0]][snake[0][1]] == 1) {
            gameover = true;
            break;
        } else if(last_dir == 9999) {
            gameover = true;
            break;
        }

        // 승리 조건
        if(victory[0] && victory[1] && victory[2] && victory[3]) {            
            last_dir = 5; cur_dir = KEY_RIGHT;
            maxsize = 3;
            GamePoint[0] = 0; GamePoint[1] = 0; GamePoint[2] = 0;
            victory[0] = false; victory[1] = false; victory[2] = false; victory[3] = false;
            level++;
        };
    }
    if(gameover == true) {
        GameOver(board);
        getch();
    }

    getch(); // 사용자입력대기
    endwin(); // Curses 모드종료
  
    return 0;
}
