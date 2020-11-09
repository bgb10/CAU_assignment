#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Nfa.h"
#include "Dfa.h"
#include "eNfa.h"

using namespace std;

int main()
{
	printf("20190942 소프트웨어학부 박관빈\nDFA, NFA, eNfa Implementation\n\n");

	//case #1: Nfa Chessboard

	printf("Case #1: Nfa Chessboard\n");
	Nfa nfa_chessboard;

	nfa_chessboard.SetStates({ '1','2','3','4','5','6','7','8','9' });
	nfa_chessboard.SetInputSymbol({ 'r','b' });
	nfa_chessboard.AddTransitionFunctionElement('1', 'r', { '2', '4' });
	nfa_chessboard.AddTransitionFunctionElement('1', 'b', { '5' });
	nfa_chessboard.AddTransitionFunctionElement('2', 'r', { '4', '6' });
	nfa_chessboard.AddTransitionFunctionElement('2', 'b', { '1', '3', '5' });
	nfa_chessboard.AddTransitionFunctionElement('3', 'r', { '2', '6' });
	nfa_chessboard.AddTransitionFunctionElement('3', 'b', { '5' });
	nfa_chessboard.AddTransitionFunctionElement('4', 'r', { '2', '8' });
	nfa_chessboard.AddTransitionFunctionElement('4', 'b', { '1', '5', '7' });
	nfa_chessboard.AddTransitionFunctionElement('5', 'r', { '2', '4', '6', '8' });
	nfa_chessboard.AddTransitionFunctionElement('5', 'b', { '1', '3', '7', '9' });
	nfa_chessboard.AddTransitionFunctionElement('6', 'r', { '2', '8' });
	nfa_chessboard.AddTransitionFunctionElement('6', 'b', { '3', '5', '9' });
	nfa_chessboard.AddTransitionFunctionElement('7', 'r', { '4', '8' });
	nfa_chessboard.AddTransitionFunctionElement('7', 'b', { '5' });
	nfa_chessboard.AddTransitionFunctionElement('8', 'r', { '4', '6' });
	nfa_chessboard.AddTransitionFunctionElement('8', 'b', { '5', '7', '9' });
	nfa_chessboard.AddTransitionFunctionElement('9', 'r', { '6', '8' });
	nfa_chessboard.AddTransitionFunctionElement('9', 'b', { '5' });
	nfa_chessboard.SetStartState('1');
	nfa_chessboard.SetFinalState({ '9' });

	nfa_chessboard.Print();
	//Nfa Chessboard accept/reject
	while (1)
	{
		string input;
		printf("\n\nNfa Chessboard test | Enter(Exit is -1): ");
		cin >> input;

		if (input == "-1") break;
		else
		{
			nfa_chessboard.Accept(input);
		}
	}

	//case #2: Nfa to Dfa Chessboard
	printf("\n\nCase #2: Nfa to Dfa Chessboard\n\n");
	Dfa dfa_chessboard = nfa_chessboard.Nfa2Dfa();

	dfa_chessboard.Print();

	//Dfa Chessboard accept/reject
	while (1)
	{
		string input;
		printf("\n\nDfa Chessboard test | Enter(Exit is -1): ");
		cin >> input;

		if (input == "-1") break;
		else
		{
			dfa_chessboard.Accept(input);
		}
	}

	//case #3: eNfa Example
	printf("\n\nCase #3: eNfa Example\n\n");
	eNfa enfa_example;

	enfa_example.SetStates({ 'A', 'B', 'C', 'D', 'E', 'F' });
	enfa_example.SetInputSymbol({ '0', '1' });
	enfa_example.AddTransitionFunctionElement('A', '0', { 'E' });
	enfa_example.AddTransitionFunctionElement('A', '1', { 'B' });
	enfa_example.AddTransitionFunctionElement('A', '#', {});
	enfa_example.AddTransitionFunctionElement('B', '0', {});
	enfa_example.AddTransitionFunctionElement('B', '1', { 'C' });
	enfa_example.AddTransitionFunctionElement('B', '#', { 'D' });
	enfa_example.AddTransitionFunctionElement('C', '0', {});
	enfa_example.AddTransitionFunctionElement('C', '1', { 'D' });
	enfa_example.AddTransitionFunctionElement('C', '#', {});
	enfa_example.AddTransitionFunctionElement('D', '0', {});
	enfa_example.AddTransitionFunctionElement('D', '1', {});
	enfa_example.AddTransitionFunctionElement('D', '#', {});
	enfa_example.AddTransitionFunctionElement('E', '0', { 'F' });
	enfa_example.AddTransitionFunctionElement('E', '1', {});
	enfa_example.AddTransitionFunctionElement('E', '#', { 'B', 'C' });
	enfa_example.AddTransitionFunctionElement('F', '0', { 'D' });
	enfa_example.AddTransitionFunctionElement('F', '1', {});
	enfa_example.AddTransitionFunctionElement('F', '#', {});
	enfa_example.SetStartState('A');
	enfa_example.SetFinalState({ 'D' });

	enfa_example.Print();

	//eNfa example accept/reject
	while (1)
	{
		string input;
		printf("\n\neNfa example test | Enter(Exit is -1): ");
		cin >> input;

		if (input == "-1") break;
		else
		{
			enfa_example.Accept(input);
		}
	}

	//case #4: eNfa to Dfa Example
	printf("\n\nCase #4: eNfa to Dfa Example\n\n");
	Dfa dfa_example = enfa_example.eNfa2Dfa();

	dfa_example.Print();

	//eNfa example accept/reject
	while (1)
	{
		string input;
		printf("\n\ndfa example test | Enter(Exit is -1): ");
		cin >> input;

		if (input == "-1") break;
		else
		{
			dfa_example.Accept(input);
		}
	}

	//case #5: Simple Dfa Example : 연속된 1이 없는 string을 accept하는 DFA
	printf("\n\nCase #5: Dfa Example: Accept all strings without two consecutive 1's\n\n");
	Dfa dfa_simple_example;

	dfa_simple_example.SetStates({ { 'A'}, {'B'}, {'C'} });
	dfa_simple_example.SetInputSymbol({ '0', '1' });
	dfa_simple_example.AddTransitionFunction({ 'A' }, '0', { 'A' });
	dfa_simple_example.AddTransitionFunction({ 'A' }, '1', { 'B' });
	dfa_simple_example.AddTransitionFunction({ 'B' }, '0', { 'A' });
	dfa_simple_example.AddTransitionFunction({ 'B' }, '1', { 'C' });
	dfa_simple_example.AddTransitionFunction({ 'C' }, '0', { 'C' });
	dfa_simple_example.AddTransitionFunction({ 'C' }, '1', { 'C' });
	dfa_simple_example.SetStartState({ 'A' });
	dfa_simple_example.SetFinalState({ {'A'}, {'B'} });

	dfa_simple_example.Print();

	//eNfa example accept/reject
	while (1)
	{
		string input;
		printf("\n\nDfa example test | Enter(Exit is -1): ");
		cin >> input;

		if (input == "-1") break;
		else
		{
			dfa_simple_example.Accept(input);
		}
	}

	printf("\nProfessor, Thank you! 교수님 감사합니다!\n20190942 소프트웨어학부 박관빈\n");
	return 0;
}