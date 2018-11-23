#ifndef IFS_H
#define IFS_H

#include "section.h"

enum IF_TYPE {IFE,ELSE_IFE,ELSEE};

class Ifs : public Section
{
    private:
        IF_TYPE ifType;
        string varname;
        bool value;
        string statement; //holds the passage to be executed in if statement
        int complete = 0;

    public:
        Ifs(string str,string str1);
        void execute(Interpreter* ins);
        string getVar();
        string getStatement();
        bool getVal();
        IF_TYPE getType();
        int getComplete() {return complete;};

};


#endif