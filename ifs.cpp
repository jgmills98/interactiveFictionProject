#include <string>

#include "ifs.h"

Ifs::Ifs(string str)
    :Section(str)
{

    if(str.find("if:") != -1)
        ifType = IFE;
    else if(str.find("else-if:") != -1)
        ifType = ELSE_IFE;
    else
        ifType = ELSEE;
    
    if(ifType == IFE || ifType == ELSE_IFE)
    {
        for(int i = str.find("$") + 1; str[i] != ' '; i++)
            varname += str[i];
        string place;

        if(str[str.find("is ") + 3] == 't')
            value = true;
        else
            value = false;

    }
    else
    {
        varname = "";
        value = false;
    }
    

    int i = str.find(")[")+2;
    int init = i;
    int brackets = 1;
    
    while(brackets != 0 && i < str.size()-1)
    {
        
        if(str[i] == '[' && i != init)
            brackets++;

        if(str[i] == ']')
            brackets--;
        
        statement += str[i];
        i++;
    }

}

string Ifs::getVar()
{
    return varname;
}

string Ifs::getStatement()
{
    return statement;
}

bool Ifs::getVal()
{
    return value;
}

IF_TYPE Ifs::getType()
{
    return ifType;
}