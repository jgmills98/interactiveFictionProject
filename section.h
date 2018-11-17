#ifndef SECTION_H
#define SECTION_H

#include <string>

using namespace std;

class Section
{
    private:
        string text;
    public:
        Section(string str) : text(str) {};
        void execute();

};

#endif