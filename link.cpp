#include <string>

#include "link.h"

Link::Link(string str)
    :Section(str)

{

    int pos = str.find("-&gt");
    if(pos == -1)
    {
        for(int i =2; i < str.size()-2;i++)
            dispText += str[i];
        
        lpassage = dispText;
    }
    else
    {
        for(int i =2; i < pos;i++)
            dispText += str[i];
        for(int i = pos+5; i< str.size()-2;i++)
            lpassage += str[i];
    }
}