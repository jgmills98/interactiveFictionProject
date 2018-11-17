#ifndef TEXT_H
#define TEXT_H

#include <string>
using namespace std;

#include "section.h"

class Text : public Section
{
    public:
        Text(string str);
        void execute();

};

#endif