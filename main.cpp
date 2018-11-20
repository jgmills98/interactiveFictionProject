#include <iostream>
#include <string>
#include "storytokenizer.h"
#include "interpreter.h"

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

    // PassageToken ptok = st.nextPassage();
    Interpreter  intp(st);



    return 0;
}