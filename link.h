#ifndef LINK_H
#define LINK_H

#include "section.h"

class Link : public Section
{
    private:
        string dispText;
        string lpassage;
    public:
        Link(const string& str);
        void execute(Interpreter* ins);
        string getPassage();
        string getText();

};
#endif