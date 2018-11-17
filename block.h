#ifndef BLOCK_H
#define BLOCK_H

#include "section.h"

class Block : public Section
{
    private:
        string textPassage;
    public:
        Block(string str);
        void executre();
        string getText();

};
#endif