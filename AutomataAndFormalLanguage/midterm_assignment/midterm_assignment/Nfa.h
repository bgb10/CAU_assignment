#ifndef NFA_H
#define NFA_H

#include "NfaTransitionFunctionElement.h"
#include "Dfa.h"
#include <vector>
#include <queue>
#include <algorithm>
#include <string>

using namespace std;

class Nfa
{
private:
    //variable
    vector<char> states;
    vector<char> input_symbol;
    vector<NfaTransitionFunctionElement> transition_function;
    char start_state;
    vector<char> final_state;

    //functions
    int Find(vector<char> src, char value); //returns index of the value
public:
    //constructor
    Nfa();

    //Functions
    Dfa Nfa2Dfa();//subset construction of Nfa
    void Print();
    void Accept(string input);

    //setter
    void SetStates(vector<char> states);
    void SetInputSymbol(vector<char> input_symbol);
    void AddTransitionFunctionElement(char state, char input_symbol, vector<char> next_states);
    void SetStartState(char start_state);
    void SetFinalState(vector<char> final_state);
    
    //getter
    vector<char> TransitionFunction(char state, char symbol);
    bool IsFinalState(char state);
};

#endif