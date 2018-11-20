// #include <iostream>
// #include <unordered_map>

#include "storytokenizer.h"
#include "interpreter.h"

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
    int pos = 0;

    while(i < passages.size())
    {
    
    }
}


