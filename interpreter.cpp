// #include <iostream>
// #include <unordered_map>

#include <queue>

#include "storytokenizer.h"

#include "block.h"
#include "goto.h"
#include "ifs.h"
#include "link.h"
#include "set.h"
#include "text.h"
#include "section.h"

using namespace std;

Interpreter::Interpreter(StoryTokenizer st)
{
    
    while(st.hasNextPassage())
    {
        PassageToken ptok = st.nextPassage();
        pass_index.emplace(ptok.getName(),passages.size());
        passages.push_back(ptok);

    }
}

void Interpreter::run()
{
    int i = 0;
    string linkChoices;
    int hitLink = 0;

    while(pos < passages.size())
    {
        hitLink = 0;
        int altered = 0;

        vector<Link> links;
        queue<Ifs> ifBlocks;

        PassageToken pt(passages[pos].getText());
        pt.setName(passages[pos].getName());
        
        PassageTokenizer ptok(pt.getText());

        while(ptok.hasNextSection())
        {

            SectionToken stok(ptok.nextSection());

            if(stok.getType() == IF || stok.getType() == ELSEIF || stok.getType() == ELSE)
            {
                string copy = stok.getText();
                stok = ptok.nextSection();
                Ifs ifs(copy,stok.getText());
                ifBlocks.push(ifs);

                stok = ptok.nextSection();
                while(stok.getType() == ELSE || stok.getType() == ELSEIF)
                {
                    copy = stok.getText();

                    stok = ptok.nextSection();

                    Ifs extra(copy,stok.getText());
                    ifBlocks.push(extra);
                }
                
                while(!ifBlocks.empty())
                {
                    ifBlocks.front().execute(this);
                    
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
            }
            else if(stok.getType() == SET)
            {
                Set st(stok.getText());
                st.execute(this);
            }
            else if(stok.getType() == TEXT)
            {
                Text tx(stok.getText());
                tx.execute(this);
            }
            else if(stok.getType() == LINK)
            {
                Link link(stok.getText());

                links.push_back(link);
                cout << "\"" << link.getText() << "\";";
                linkChoices += "\"" + link.getText() + "\";\n";
                hitLink = 1;
            }
            else if(stok.getType() == GOTO)
            {
                Goto gt(stok.getText());
                gt.execute(this);
                break;
            }
        }

        if(hitLink == 1)
        {
            cout << "\n" << linkChoices << endl;
            string choice;
            getline(cin,choice);

            for(int i = 0; i < links.size(); i++)
            {
                if(choice == links[i].getText())
                {
                    links[i].execute(this);
                    linkChoices = "";
                }
            }
        }

        if(pt.getName() == passages[passages.size()-1].getName())
            break;

    }
}


