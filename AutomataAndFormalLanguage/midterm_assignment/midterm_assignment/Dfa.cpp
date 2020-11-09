#include "Dfa.h"

Dfa::Dfa()
{
}

void Dfa::SetStates(vector<vector<char>> states)
{
	this->states = states;
}

void Dfa::AddState(vector<char> state)
{
	this->states.push_back(state);
}

void Dfa::SetInputSymbol(vector<char> input_symbol)
{
	this->input_symbol = input_symbol;
}

void Dfa::AddTransitionFunction(vector<char> state, char input_symbol, vector<char> next_state)
{
	DfaTransitionFunctionElement element(state, input_symbol, next_state);
	this->transition_function.push_back(element);
}

vector<char> Dfa::TransitionFunction(vector<char> state, char symbol)
{
	//해당 transition function이 있으면 next_states, 없으면 {}(empty vector) 반환
	for (auto element : this->transition_function)
	{
		if (element.GetState() == state && element.GetInputSymbol() == symbol)
		{
			return element.GetNextState();
		}
	}

	vector<char> empty_vector;

	return empty_vector;
}

void Dfa::SetStartState(vector<char> start_state)
{
	this->start_state = start_state;
}

void Dfa::SetFinalState(vector<vector<char>> final_state)
{
	this->final_state = final_state;
}

void Dfa::AddFinalState(vector<char> final_state_element)
{
	if (Find(final_state, final_state_element) == -1)
	{
		this->final_state.push_back(final_state_element);
	}
}

int Dfa::Find(vector<vector<char>> src, vector<char> value)
{
	int result;

	result = std::find(src.begin(), src.end(), value) - src.begin(); //값이 존재하는 경우 index 반환

	if (result == src.size()) result = -1; //값이 존재하지 않는 경우 -1 반환

	return result;
}

bool Dfa::IsStateExists(vector<char> state)
{
	for (auto element : this->states)
	{
		if (element == state)
		{
			return true;
		}
	}

	return false;
}

void Dfa::Print()
{
	//교수님이 보여주신 예제 화면 양식과 비슷하게 구성
	//States
	printf("Q (states): \n");
	for (int i = 0; i < states.size(); i++)
	{
		printf("%d) ", i + 1);
		for (int j = 0; j < states[i].size(); j++)
		{
			printf("%c ", states[i][j]);
		}
		printf("\n");
	}

	//Sigma
	printf("Sigma (input symbols): \n");
	for (int i = 0; i < input_symbol.size(); i++)
	{
		printf("%d) %c\n", i + 1, input_symbol[i]);
	}

	//Delta
	printf("Delta (transition function): \n");
	for (int i = 0; i < this->transition_function.size(); i++)
	{
		printf("%d) ", i+1);
		transition_function[i].Print();
	}

	//q0
	printf("q0 (start state): ");
	for (auto start_state_element : start_state)
	{
		printf("%c", start_state_element);
	}
	printf("\n");

	//F
	printf("F (final states): ");
	for (auto final_state_element : final_state)
	{
		for (auto final_state_element_element : final_state_element)
		{
			printf("%c", final_state_element_element);
		}
		printf(" ");
	}
	printf("\n");
}

void Dfa::Accept(string input)
{
	vector<char> current_state = start_state;
	vector<char> temp_state;

	for (auto symbol : input)
	{
		current_state = TransitionFunction(current_state, symbol);
		if (current_state.empty())
		{
			printf("False!\n");
			return;
		}
	}

	if (Find(final_state, current_state) != -1)
	{
		printf("True!\n");
	}
	else
	{
		printf("False!\n");
	}

	return;
}