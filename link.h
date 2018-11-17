#ifndef BLOCK_H
#define BLOCK_H

#include "section.h"

class Link : public Section
{
    private:
        string dispText;
        string lpassage;
    public:
        Link(string str);
        void executre();
        string getPassage();
        string getText();

};
#endif