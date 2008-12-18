/*  Filename:  convert.cpp

    Author:  Br. David Carlson

    Date:  July 9, 1999

    Revised:  August 1, 2000

    This program repeatedly prompts the user to enter an infix expression
    and converts it to postfix, which is printed on the screen.

    Reference:  The basic algorithm and background material can be found
    in Data Structures Using Pascal, 2nd ed. Tenenbaum and Augenstein.
    Prentice-Hall (1986).  See chapter 2.
*/

#include <iostream>
#include <string>
#include <stack>

using namespace std;


void Convert(const string & Infix, string & Postfix);

bool IsOperand(char ch);

bool TakesPrecedence(char OperatorA, char OperatorB);


int main(void)
{
    char Reply;

    do {
        string Infix, Postfix;   // local to this loop

        cout << "Enter an infix expression (e.g. (a+b)/c^2, with no spaces):"
        << endl;
        cin >> Infix;

        Convert(Infix, Postfix);
        cout << "The equivalent postfix expression is:" << endl
        << Postfix << endl;
        cout << endl << "Do another (y/n)? ";
        cin >> Reply;
    }
    while (tolower(Reply) == 'y');

    return 0;
}


/* Given:  ch   A character.
   Task:   To determine whether ch represents an operand (here understood
           to be a single letter or digit).
   Return: In the function name: true, if ch is an operand, false otherwise.
*/
bool IsOperand(char ch)
{
    if (((ch >= 'a') && (ch <= 'z')) ||
        ((ch >= 'A') && (ch <= 'Z')) ||
        ((ch >= '0') && (ch <= '9')))
        return true;
    else
        return false;
}


/* Given:  OperatorA    A character representing an operator or parenthesis.
           OperatorB    A character representing an operator or parenthesis.
   Task:   To determine whether OperatorA takes precedence over OperatorB.
   Return: In the function name: true, if OperatorA takes precedence over
           OperatorB.
*/
bool TakesPrecedence(char OperatorA, char OperatorB)
{
    if (OperatorA == '(')
        return false;
    else if (OperatorB == '(')
        return false;
    else if (OperatorB == ')')
        return true;                                       // A character representing an operator or parenthesis.  
    else if ((OperatorA == '^') && (OperatorB == '^'))     // A character representing an operator or parenthesis.  
        return false;                                      // whether OperatorA takes precedence over OperatorB.    
    else if (OperatorA == '^')                             // on name: true, if OperatorA takes precedence over     
        return true;                                                                                              
    else if (OperatorB == '^')                                                                                 
        return false;                                              
    else if ((OperatorA == '*') || (OperatorA == '/'))             
        return true;                                               
    else if ((OperatorB == '*') || (OperatorB == '/'))             
        return false;                                              
    else                                                           
        return true;                                               
                                                                   
}


/* Given:  Infix    A string representing an infix expression (no spaces).
   Task:   To find the postfix equivalent of this expression.
   Return: Postfix  A string holding this postfix equivalent.
*/
void Convert(const string & Infix, string & Postfix)
{
    stack<char> OperatorStack;
    char TopSymbol, Symbol;
    int k;

    for (k = 0; k < Infix.size(); k++) {
        Symbol = Infix[k];
        if (IsOperand(Symbol))
            Postfix = Postfix + Symbol;
        else {
            while ((! OperatorStack.empty()) &&
                   (TakesPrecedence(OperatorStack.top(), Symbol))) {
                TopSymbol = OperatorStack.top();
                OperatorStack.pop();
                Postfix = Postfix + TopSymbol;
            }
            if ((! OperatorStack.empty()) && (Symbol == ')'))
                OperatorStack.pop();   // discard matching (
            else
                OperatorStack.push(Symbol);
        }
    }

    while (! OperatorStack.empty()) {
        TopSymbol = OperatorStack.top();
        OperatorStack.pop();
        Postfix = Postfix + TopSymbol;
    }
}
