#ifndef ENFATRANSITIONFUNCTIONELEMENT_H
#define ENFATRANSITIONFUNCTIONELEMENT_H

#include <vector>

using namespace std;

class eNfaTransitionFunctionElement //eNfaTransitionFunctionElement
{
private:
    //variable
    char state;
    char input_symbol; //epsilon is '#'
    vector<char> next_states;

public:
    eNfaTransitionFunctionElement();
    eNfaTransitionFunctionElement(char state, char input_symbol, vector<char> next_states);

    char GetState();
    char GetInputSymbol();
    vector<char> GetNextStates();
};

#endif