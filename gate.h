#include <vector>
#include <iostream>
using namespace std;

class Gate {
public:
    vector<pair<int,int>> gateList;
    pair<int,int>& gate1;
    pair<int,int>& gate2;
}