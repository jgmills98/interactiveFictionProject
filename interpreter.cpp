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
    //loops through all passages to add PassageTokens to the map and vector
    while(st.hasNextPassage())
    {
        PassageToken ptok = st.nextPassage();
        pass_index.emplace(ptok.getName(),passages.size());
        passages.push_back(ptok);

    }
}

void Interpreter::run()
{
    string linkChoices;//string that stores all links that will be printed at the end of the passage
    int hitLink; //used to check if there are any links in the Passage
    int finished = 0; //allows 1 more pass through once at the end of the game

    while(finished == 0) //loops while through passages while remaining within bounds
    {
        if(passages[pos].getName() == passages[passages.size()-1].getName())
            finished = 1;
        
        hitLink = 0;//default to 0 until a link is found

        vector<Link> links;//vector used to store all links found in each passage
        queue<Ifs> ifBlocks;//queue used to store each if statement block. queue in order to follow first in first out 

        PassageTokenizer ptok(passages[pos].getText()); //uses the passage vector for the tokenizer

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
            cout << endl;

            for(int i = 0; i < links.size(); i++)
            {
                if(choice == links[i].getText())
                {
                    links[i].execute(this);
                    linkChoices = "";
                }
            }
        }

    }
}


