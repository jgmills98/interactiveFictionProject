#include <string>

#include "set.h"

Set::Set(string str)
    :Section(str)
{
    string val;

    int pos = str.find("$");
    for(int i = pos + 1; str[i] != ' '; i++)
        varname += str[i];
    
    pos = str.find("to ");
    for(int i = pos + 3; i < str.size()-1;i++)
        val += str[i];
    if(val == "true")
        value = true;
    else
        value = false;
    
}

void Set::execute(Interpreter* ins)
{
    if(ins->vars.find(varname) == ins->vars.end())   
        ins->vars.emplace(varname,value);
    else
        ins->vars[varname] = value;
    
}

string Set::getVar()
{
    return varname;
}

bool Set::getVal()
{
    return value;
}