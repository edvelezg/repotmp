#include <stack>
#include <iostream>

using namespace std;

int main (int argc, char const *argv[])
{
	std::stack<int> intStack;

    int a, b;                                     // operands

    string query = "38+6-4*";

    for(size_t i = 0; i < query.size(); ++i)
    {
        if (query.at(i) >= 48 && query.at(i) <=57)
        {
            intStack.push((int)(query.at(i) - 48));
        }
        else
        {
            int b = intStack.top();
            intStack.pop();
            int a = intStack.top();
            intStack.pop();

            switch (query.at(i))
            {
                case '+':
                    intStack.push( a + b );
                    break;
                case '-':
                    intStack.push ( a - b );
                    break;
                case '*':
                    intStack.push( a * b );
                    break;
                case '/':
                    intStack.push( a / b );
                    break;
                default:
                    intStack.push ( a );
                    intStack.push ( b );
                    break;
            }
        }
    }
	cout << "The answer is: " << intStack.top() << endl;

    return 0;
}
