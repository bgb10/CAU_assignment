#ifndef DFATRANSITIONFUNCTIONELEMENT_H
#define DFATRANSITIONFUNCTIONELEMENT_H

#include <vector>

using namespace std;

class DfaTransitionFunctionElement
{
private:
    //variable
    vector<char> state;
    char input_symbol;
    vector<char> next_state;

public:
    DfaTransitionFunctionElement(vector<char> state, char input_symbol, vector<char> next_state);

    //getter
    vector<char> GetState();
    char GetInputSymbol();
    vector<char> GetNextState();
    void Print();
};

#endif