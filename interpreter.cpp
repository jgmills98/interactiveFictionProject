// #include <iostream>
// #include <unordered_map>

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

        vector<Link> links;

        PassageToken pt(passages[pos].getText());
        
        PassageTokenizer ptok(pt.getText());

        while(ptok.hasNextSection())
        {

            SectionToken stok(ptok.nextSection());

            if(stok.getType() == SET)
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
            // else if(stok.getType() == TEXT)
            // {
            //     Text tx(stok.getText());
            //     tx.execute(this);
            // }
            // else if(stok.getType() == TEXT)
            // {
            //     Text tx(stok.getText());
            //     tx.execute(this);
            // }

        }
        if(hitLink == 1)
        {
            cout << "\n\n" << linkChoices << endl;
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


    }
}


