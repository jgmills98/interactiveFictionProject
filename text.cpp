#include "text.h"

Text::Text(string str)
    :Section(str)
{

}

void Text::execute(Interpreter* ins)
{
    cout << getText();
}
