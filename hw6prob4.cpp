// Name: Anthony T. Pham
// UF ID: 5038-1111
// Discussion section #: 1079

#include<iostream>
#include<fstream>
#include<string>
#include<stack>
#include "hw6.h"

using namespace std;

// method to convert an infix expression to a postfix expression
string infixToPostfix(string infix)
{
	// create variable to hold postfix expression
	string postfix;
	// create stack to help with the infix to postfix conversion
	stack<char> mystack;

	// modify infix expression to change any negative signs to the unary operator "?"
	if(infix.at(0) == '-')
		infix.at(0) = '?';
	for(int i = 1; i < infix.length(); i++)
	{
		if(infix.at(i) == '-' && (infix.at(i-1) == '?' || infix.at(i-1) == '(' || infix.at(i-1) == '+' || infix.at(i-1) == '-' || infix.at(i-1) == '*' || infix.at(i-1) == '/'))
			infix.at(i) = '?';
	}

	// calculate postfix expression
	for(int i = 0; i < infix.length(); i++)
	{
		// if the stack is empty
		if(mystack.empty())
		{
			// if the character is an operator push it into the stack
			if(infix.at(i) == '?' || infix.at(i) == '(' || infix.at(i) == '+' || infix.at(i) == '-' || infix.at(i) == '*' || infix.at(i) == '/')
				mystack.push(infix.at(i));
			// if it's an operator then it should be an operand, in that case add it to the postfix expression
			else
				postfix = postfix + infix.at(i);
		}
		else if(!mystack.empty()) // if the stack is not empty
		{
			// if the character scanned is a left parentheses, push it onto the stack
			if(infix.at(i) == '(')
			{
				mystack.push(infix.at(i));
			}
			// else if the character scanned is a right parentheses, pop operators out of the stack and add them to the postfix
			// expression until we reach a left parentheses
			else if(infix.at(i) == ')')
			{
				int j = i + 1;

				while(mystack.top() != '(')
				{
					postfix = postfix + mystack.top();
					mystack.pop();
				}
				// pop the left parentheses out
				mystack.pop();

				// if a right parentheses is followed by a left parentheses (ie. (a+b)(c+d)),
				// add a '*' operator to the stack
				if(j < infix.length() && infix.at(j) == '(')
				{
					mystack.push('*');
				}
			}
			// else if the character scanned is the unary operator '?', which has the highest precedence, push it onto the stack
			else if(infix.at(i) == '?')
			{
				mystack.push(infix.at(i));
			}
			// else if the character scanned is the operator '*' or '/', pop operators out of the stack and add them to
			// the postfix expression until we reach a '+' or '-' operator (pop out all operators that are equal to or higher precendence
			// than '*' or '/')
			else if(infix.at(i) == '*' || infix.at(i) == '/')
			{
				while(!mystack.empty() && mystack.top() != '+' && mystack.top() != '-' && mystack.top() != '(')
				{
					postfix = postfix + mystack.top();
					mystack.pop();
				}
				mystack.push(infix.at(i));
			}
			// else if the character scanned is the operator '+' or '/', pop operators out of the stack and add them to
			// the postfix expression (pop out all operators that are equal to or higher precedence than '+' or '-', which is
			// basically all operators for this problem)
			else if(infix.at(i) == '+' || infix.at(i) == '-')
			{
				while(!mystack.empty() && mystack.top() != '(')
				{
					postfix = postfix + mystack.top();
					mystack.pop();
				}
				mystack.push(infix.at(i));
			}
			else
			{
				// if the last operator scanned was the unary operator '?', which has the highest precedence and the character scanned
				// is an operand, then add the operand to postfix expression and then add the operator to the postfix expression
				if(mystack.top() == '?' && (infix.at(i) != '?' || infix.at(i) != '(' || infix.at(i) != '+' || infix.at(i) != '-' || infix.at(i) != '*' || infix.at(i) != '/'))
				{
					postfix = postfix + infix.at(i) + mystack.top();
					mystack.pop();
				}
				// if the last operator scanned was the unary operator '?' and the character scanned is an operator, add the unary operator
				// to the postfix expression
				else if(mystack.top() == '?' && (infix.at(i) == '+' || infix.at(i) == '-' || infix.at(i) == '*' || infix.at(i) == '/'))
				{
					postfix = postfix + mystack.top();
					mystack.pop();
				}
				// else the character scanned should be an operand, so just add it to the postfix expression
				else
				{
					postfix = postfix + infix.at(i);
				}
			}

		}
	}

	// add the rest of the operators to the postfix expression
	while(!mystack.empty())
	{
		postfix = postfix + mystack.top();
		mystack.pop();
	}
	// return the postfix expression
	return postfix;
}

int main()
{
	// declaration of variables
	ifstream inFile;
	inFile.open("hw6prob4in");
	ofstream outFile("hw6prob4out");
	string infix, postfix;

	// read in infix expression
	inFile >> infix;
	// convert to postfix expression and write postfix expression into file
	postfix = infixToPostfix(infix);
	outFile << postfix << endl;

	cout << "Writing to file complete." << endl;
	// close file streams
	inFile.close();
	outFile.close();

	return 0;
}
