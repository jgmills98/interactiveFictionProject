#ifndef SECTION_H
#define SECTION_H

#include <string>
#include "interpreter.h"

using namespace std;

class Section
{
    private:
        string text;
    public:
        Section(string str) : text(str) {};
        void execute(Interpreter* ins);
        string getText(){return text;};

};

#endif