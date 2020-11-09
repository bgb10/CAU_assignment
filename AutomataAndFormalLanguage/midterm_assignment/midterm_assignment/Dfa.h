#ifndef DFA_H
#define DFA_H

#include "DfaTransitionFunctionElement.h"
#include <vector>
#include <string>

using namespace std;

class Dfa
{
private:
    //variable
    vector<vector<char>> states;
    vector<char> input_symbol;
    vector<DfaTransitionFunctionElement> transition_function;
    vector<char> start_state;
    vector<vector<char>> final_state;
public:
    //functions
    Dfa();
    void SetStates(vector<vector<char>> states);
    void AddState(vector<char> state);
    void SetInputSymbol(vector<char> input_symbol);
    void AddTransitionFunction(vector<char> state, char input_symbol, vector<char> next_state);
    void SetStartState(vector<char> start_state);
    void SetFinalState(vector<vector<char>> final_state);
    void AddFinalState(vector<char> final_state_element);

    int Find(vector<vector<char>> src, vector<char> value); //returns index of the value

    vector<char> TransitionFunction(vector<char> state, char symbol);
    bool IsStateExists(vector<char> state);

    void Print();
    void Accept(string input);
};

#endif