#include <iostream>
#include <unordered_map>

#include <queue>
#include "interpreter.h"
#include "storytokenizer.h"

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
	hitLink = 0;
}

void Interpreter::run()
{
    int finished = 0; //allows 1 more pass through once at the end of the game
	

    while(finished == 0) //loops while through passages while remaining within bounds
    {
       
		hitLink = 0;
		hitGoto = 0;
		links.clear();

        queue<Ifs> ifBlocks;//queue used to store each if statement block. queue in order to follow first in first out 

        PassageTokenizer ptok(passages[pos].getText()); //uses the passage vector for the tokenizer
		
		
        while(ptok.hasNextSection())
        {
			
			
			SectionToken stok(ptok.nextSection());
			
            //checks if the current section is an if/elseif/else and finds its block
			if (stok.getType() == IF || stok.getType() == ELSEIF || stok.getType() == ELSE)
			{
				string copy = stok.getText();
				stok = ptok.nextSection();
				Ifs ifs(copy, stok.getText());
				ifBlocks.push(ifs);

				stok = ptok.nextSection();
                //if there are any elseif/else related to the previous if statement, that gets added to the queue as well
				while (stok.getType() == ELSE || stok.getType() == ELSEIF)
				{
					copy = stok.getText();

					stok = ptok.nextSection();

					Ifs extra(copy, stok.getText());						
					ifBlocks.push(extra);

				}
				
				
                while(!ifBlocks.empty())
                {
                    ifBlocks.front().execute(this);//executes the front if statement
                    
                    if(ifBlocks.front().getComplete() == 1)//if that executes properly, removes the other elseifs or else from the queue
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
					st.execute(this);
				}
				else if (stok.getType() == TEXT)
				{
					Text tx(stok.getText());
					tx.execute(this);
				}
				else if (stok.getType() == LINK)
				{
					Link* link = new Link(stok.getText());
					cout << link->getText();
					links.push_back(link);

					hitLink = 1;
				}
				else if (stok.getType() == GOTO)
				{
					Goto gt(stok.getText());
					gt.execute(this);
					hitGoto = 1;
					break;
				}

				if (hitGoto == 1)
					break;


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
                Link* link = new Link(stok.getText());
				cout << link->getText();
                links.push_back(link);
				
                hitLink = 1;
            }
            else if(stok.getType() == GOTO)
            {
                Goto gt(stok.getText());
                gt.execute(this);
				hitGoto = 1;
                break;
            }

			if (hitGoto == 1)
				break;
        }

		//Ends Program if passage with no Links or Gotos is ran
		if ((hitLink == 0) && (hitGoto == 0))
			finished = 1;

        if(hitLink == 1)
        {
			int choicecount = 0;
			cout << "\n"<< endl;
			
			for (int i = 0; i < links.size(); i++) //prints ll the link choices
			{
				cout << i + 1 << ". " << links[i]->getText() << endl;
				choicecount++;
			}
            int choice;
			cin >> choice;
			
			while (!cin || choice < 1 || choice > choicecount) //takes user input for the passage they want to go to
			{
				cout << "Invalid Choice, Re-enter a number between 1 and " << choicecount << ": ";
				cin.clear();
				cin.ignore(10000, '\n');
				cin >> choice;
			}
            
			links[choice - 1]->execute(this);//moves to the passage that the user selected
			
        }

    }
}


