#ifndef ENFA_H
#define ENFA_H

#include "eNfaTransitionFunctionElement.h"
#include "Dfa.h"
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class eNfa
{
private:
    //variable
    vector<char> states;
    vector<char> input_symbol;
    vector<eNfaTransitionFunctionElement> transition_function;
    char start_state;
    vector<char> final_state;

    //functions
    int Find(vector<char> src, char value); //returns index of the value
public:
    //constructor
    eNfa();

    //Functions
    Dfa eNfa2Dfa();//subset construction of Nfa
    vector<char> CL(vector<char> state);
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