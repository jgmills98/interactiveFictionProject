#include <string>
#include <queue>

#include "block.h"
#include "goto.h"
#include "ifs.h"
#include "link.h"
#include "set.h"
#include "text.h"

Ifs::Ifs(string str,string str1)
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
    
    statement = str1.substr(1,str1.size()-2);

}

void Ifs::execute(Interpreter* ins)
{
   
    if(((ifType == IFE || ifType == ELSE_IFE) && ins->vars[varname] == value) || ifType == ELSEE)
    {
        queue<Ifs> ifBlocks;
        
        complete = 1;
        PassageTokenizer ptok(statement);
        
        while(ptok.hasNextSection())
        {
            SectionToken stok = ptok.nextSection();
            if(stok.getType() == IF || stok.getType() == ELSEIF || stok.getType() == ELSE)
            {
                string copy = stok.getText();

                stok = ptok.nextSection();

                Ifs ifs(copy,stok.getText());

                ifBlocks.push(ifs);

                stok = ptok.nextSection();
				
				while (stok.getType() == ELSE || stok.getType() == ELSEIF)
				{
					copy = stok.getText();

					stok = ptok.nextSection();

					Ifs extra(copy, stok.getText());
					ifBlocks.push(extra);

				}
				
		
                while(!ifBlocks.empty())
                {
                    ifBlocks.front().execute(ins);
                    
                    if(ifBlocks.front().getComplete() == 1)
                    {
                        while(!ifBlocks.empty())
                            ifBlocks.pop();
                    }
                    else
                    {
                        ifBlocks.pop();
                    }
                }

				if (stok.getType() == SET)
				{
					Set st(stok.getText());
					st.execute(ins);
				}
				else if (stok.getType() == TEXT)
				{
					Text tx(stok.getText());
					tx.execute(ins);
				}
				else if (stok.getType() == LINK)
				{
					Link* link = new Link(stok.getText());
					cout << link->getText();
					ins->links.push_back(link);

					ins->hitLink = 1;
				}
				else if (stok.getType() == GOTO)
				{
					Goto gt(stok.getText());
					gt.execute(ins);
					ins->hitGoto = 1;
					break;
				}

				if (ins->hitGoto == 1)
					break;

            }
           else if(stok.getType() == SET)
            {
                Set st(stok.getText());
                st.execute(ins);
            }
            else if(stok.getType() == TEXT)
            {
                Text tx(stok.getText());
                tx.execute(ins);
            }
            else if(stok.getType() == LINK)
            {
				Link* link = new Link(stok.getText());
				cout << link->getText();
				ins->links.push_back(link);

                ins->hitLink = 1;

            }
            else if(stok.getType() == GOTO)
            {
                Goto gt(stok.getText());
                gt.execute(ins);
				ins->hitGoto = 1;
                break;
            }
        }
    }
    // else if(ifType == ELSEE)
    // {
    //     complete = 1;
    //     PassageTokenizer ptok(statement);

    //     while(ptok.hasNextSection())
    //     {
    //         SectionToken stok = ptok.nextSection();
    //         if(stok.getType() == TEXT)
    //         {
    //             Text tx(stok.getText());
    //             tx.execute(ins);
    //         }
    //     }
    // }

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