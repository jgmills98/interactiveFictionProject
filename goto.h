#ifndef BLOCK_H
#define BLOCK_H

#include "section.h"

class Goto : public Section
{
    private:
        string gpassage;
    public:
        Goto(string str);
        void executre();
        string getPassage();


};

#endif