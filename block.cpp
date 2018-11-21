#include <string>

#include "block.h"

Block::Block(string str)
	:Section(str)
{
	
	for (int i = 1; i < str.size()-1; i++)
	{
		textPassage += str[i];
	}

}


string Block::getText()
{
	return textPassage;
}