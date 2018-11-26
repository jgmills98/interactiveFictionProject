#ifndef __INTERPRETER_H
#define __INTERPRETER_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include "storytokenizer.h"

using namespace std;

class Interpreter
{
    private:
        int pos = 0;
    public:
        unordered_map<string,int> pass_index;
        unordered_map<string,bool> vars;
        vector<PassageToken> passages;
        Interpreter(StoryTokenizer st);
        void run(string str);
        void run(int index);
        void run();
        int findIndex(string name);
        void updateVar(string name, bool val);
        bool getVal(string name);
        int getPos() {return pos;};
        void setPos(int x) {pos = x;};

};
#endif