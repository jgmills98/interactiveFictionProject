#include <iostream>
#include <string>
#include <fstream>
#include "storytokenizer.h"
#include "interpreter.h"
/*
#include "set.h" //remove later, used to test constructors
#include "section.h"
#include "link.h"
#include "ifs.h"
#include "text.h"
*/
using namespace std;

int main()
{
    string line, story;

	ifstream in;
	in.open("if.html"); //Change file name to test diferent files
	if (!in.is_open())
	{
		cout << "Could not open file" << endl;
		return 1;
	}

    getline(in, line);
    while (in && line != "</html>")
    {
        story += line + '\n';
        getline(in, line);
    }
	in.close();
    StoryTokenizer st(story);

    Interpreter  intp(st);    
    intp.run();

    return 0;
}