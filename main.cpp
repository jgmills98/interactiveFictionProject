#include <iostream>
#include <string>
#include "storytokenizer.h"
// #include "interpreter.h"

#include "set.h" //remove later, used to test constructors
#include "section.h"
#include "link.h"
#include "ifs.h"
#include "text.h"

using namespace std;

int main()
{
    string line, story;
    getline(cin, line);
    while (cin && line != "</html>")
    {
        story += line + '\n';
        getline(cin, line);
    }
    StoryTokenizer st(story);

    Interpreter  intp(st);    

    intp.run();

    return 0;
}