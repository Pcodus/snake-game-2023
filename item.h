vector<G> growitems;
vector<P> poisonitems;

extern int level = 0;
void GenerateGrowth(int map[][24][45]);
void GeneratePoison(int map[][24][45]);

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