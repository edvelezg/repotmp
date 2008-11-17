#include "mylib.h"

class A;
A::A(int newa) : a(newa) 
{ 
}
int A::getValue() const 
{ 
	return a; 
}
void A::setValue(int newa) 
{ 
	a = newa; 
} 