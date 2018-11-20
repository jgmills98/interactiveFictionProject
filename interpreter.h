#include <iostream>
#include <vector>
#include <unordered_map>
#include "storytokenizer.h"

using namespace std;

class Interpreter
{
    private:
        vector<PassageToken> passages;
        unordered_map<string,bool> vars;
        unordered_map<string,int> pass_index;
    public:
        Interpreter(StoryTokenizer st);
        void run(string str);
        void run(int index);
        void run();
        int findIndex(string name);
        void updateVar(string name, bool val);
        bool getVal(string name);

};