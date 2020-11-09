#ifndef NFATRANSITIONFUNCTIONELEMENT_H
#define NFATRANSITIONFUNCTIONELEMENT_H

#include <vector>

using namespace std;

class NfaTransitionFunctionElement //NfaTransitionFunctionElement
{
private:
    //variable
    char state;
    char input_symbol;
    vector<char> next_states;

public:
    NfaTransitionFunctionElement();
    NfaTransitionFunctionElement(char state, char input_symbol, vector<char> next_states);

    char GetState();
    char GetInputSymbol();
    vector<char> GetNextStates();
};

#endif