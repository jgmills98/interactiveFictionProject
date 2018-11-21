#include <string>

#include "goto.h"

Goto::Goto(string str)
	:Section(str)
{	
	int pos = str.find("&quot;");
	for (int i = pos + 6; str[i] != '&'; i++)
	{
		gpassage += str[i];
	}

}


string Goto::getPassage()
{
	return gpassage;
}