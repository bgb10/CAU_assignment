#include "eNfaTransitionFunctionElement.h"

eNfaTransitionFunctionElement::eNfaTransitionFunctionElement()
{
}

eNfaTransitionFunctionElement::eNfaTransitionFunctionElement(char state, char input_symbol, vector<char> next_states)
{
	this->state = state;
	this->input_symbol = input_symbol;
	this->next_states = next_states;
}

char eNfaTransitionFunctionElement::GetState()
{
	return this->state;
}
char eNfaTransitionFunctionElement::GetInputSymbol()
{
	return this->input_symbol;
}
vector<char> eNfaTransitionFunctionElement::GetNextStates()
{
	return this->next_states;
}