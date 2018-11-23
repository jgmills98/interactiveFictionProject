#include <string>

#include "link.h"

Link::Link(const string& str)
    :Section(str)
{

    int pos = str.find("-&gt");
    if(pos == -1)
    {
        dispText = str.substr(2,str.size()-4);
        lpassage = dispText;
    }
    else
    {
        dispText = str.substr(2,str.size()-pos+1);
        lpassage = str.substr(pos+5,str.size()-pos-7);  
    }
    
}

void Link::execute(Interpreter* ins)
{

    ins->setPos(ins->pass_index[lpassage]);
}

string Link::getText()
{
    return dispText;
}

string Link::getPassage()
{
    return lpassage;
}