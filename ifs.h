#ifndef BLOCK_H
#define BLOCK_H

#include "section.h"

enum IF_TYPE {IF,ELSE_IF,ELSE};

class Ifs : public Section
{
    private:
        IF_TYPE ifType;
        string varname;
        int value;
    public:
        Ifs(string str);
        void execute();
        string getVar();
        int getVal();

};


#endif