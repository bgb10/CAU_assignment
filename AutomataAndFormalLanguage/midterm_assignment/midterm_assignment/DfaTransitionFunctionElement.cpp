#include "DfaTransitionFunctionElement.h"

DfaTransitionFunctionElement::DfaTransitionFunctionElement(vector<char> state, char input_symbol, vector<char> next_state)
{
	this->state = state;
	this->input_symbol = input_symbol;
	this->next_state = next_state;
}

vector<char> DfaTransitionFunctionElement::GetState()
{
	return this->state;
}
char DfaTransitionFunctionElement::GetInputSymbol()
{
	return this->input_symbol;
}
vector<char> DfaTransitionFunctionElement::GetNextState()
{
	return this->next_state;
}

void DfaTransitionFunctionElement::Print()
{
	printf("(");
	for (auto state_element : GetState())
	{
		printf("%c", state_element);
	}
	printf(",");
	printf("%c", GetInputSymbol());
	printf(") = ");
	for (auto next_state_element : GetNextState())
	{
		printf("%c", next_state_element);
	}
	printf("\n");
}