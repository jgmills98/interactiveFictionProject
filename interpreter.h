#ifndef __INTERPRETER_H
#define __INTERPRETER_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include "storytokenizer.h"



using namespace std;
class Link;
class Interpreter
{
    private:
        int pos = 0;
    public:
        unordered_map<string,int> pass_index;
        unordered_map<string,bool> vars;
        vector<PassageToken> passages;
		vector<Link*> links;
        Interpreter(StoryTokenizer st);
        void run();
		int hitLink;
		int hitGoto;
        int getPos() {return pos;};
        void setPos(int x) {pos = x;};

};
#endif