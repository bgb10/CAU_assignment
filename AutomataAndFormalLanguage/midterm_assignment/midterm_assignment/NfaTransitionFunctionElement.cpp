#include "NfaTransitionFunctionElement.h"

NfaTransitionFunctionElement::NfaTransitionFunctionElement()
{
}

NfaTransitionFunctionElement::NfaTransitionFunctionElement(char state, char input_symbol, vector<char> next_states)
{
	this->state = state;
	this->input_symbol = input_symbol;
	this->next_states = next_states;
}

char NfaTransitionFunctionElement::GetState()
{
	return this->state;
}
char NfaTransitionFunctionElement::GetInputSymbol()
{
	return this->input_symbol;
}
vector<char> NfaTransitionFunctionElement::GetNextStates()
{
	return this->next_states;
}