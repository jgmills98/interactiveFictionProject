#ifndef BLOCK_H
#define BLOCK_H

#include "section.h"

class Set : public Section
{
    private:
        string varname;
        bool value;
    public:
        Set(string str);
        void execute();
        string getVar();
        bool getVal();
};
#endif