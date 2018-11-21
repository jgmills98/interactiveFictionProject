#ifndef GOTO_H
#define GOTO_H

#include "section.h"

class Goto : public Section
{
    private:
        string gpassage;
    public:
        Goto(string str);
        void execute();
        string getPassage();


};

#endif