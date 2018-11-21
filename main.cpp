#include <iostream>
#include <string>
#include "storytokenizer.h"
#include "interpreter.h"

#include "set.h" //remove later, used to test constructors
#include "section.h"
#include "link.h"
#include "ifs.h"

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

    Ifs test("(else:)[??????]");
    cout << test.getVar() << endl;
    cout << test.getVal() << endl;
    cout << test.getStatement() << endl;


    return 0;
}