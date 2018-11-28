#include <iostream>
#include <string>
#include <fstream>
#include "storytokenizer.h"
#include "interpreter.h"

using namespace std;

int main()
{
    string line, story;

	ifstream in;
	in.open("if.html"); //open if.html
	if (!in.is_open())
	{
		cout << "Could not open file" << endl;
		return 1;
	}

    getline(in, line);
    while (in && line != "</html>")//take all of the data from the if.html 
    {
        story += line + '\n';
        getline(in, line);
    }
	in.close();
    StoryTokenizer st(story);//tokenizes all of the data taken from the if.html

    Interpreter  intp(st); //passes the story into the interpreters construction  
    intp.run(); //runs through the entire interactive fiction

    return 0;
}