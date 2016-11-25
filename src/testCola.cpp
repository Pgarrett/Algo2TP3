#include <iostream>
#include <fstream>
#include "ColaMinPrior.h"
#include "mini_test.h"

using namespace std;
using namespace aed2;

void test_crear(){
	ColaMinPrior<int> cl;
	ASSERT(!false);
}

void test_encolar(){
	ColaMinPrior<int> cl;
	cl.Encolar(4,1);
	cout << cl << endl;
	cl.Encolar(2,2);
	cout << cl << endl;
	cl.Encolar(6,3);
	cout << cl << endl;
	cl.Encolar(5,4);
	cout << cl << endl;
	cl.Encolar(4,5);
	cout << cl << endl;
	cl.Encolar(23,6);
	cout << cl << endl;
	cl.Encolar(1,7);
	cout << cl << endl;
	ASSERT(cl.Tamano() == 7);
}

int main() {

	RUN_TEST(test_crear);
	RUN_TEST(test_encolar);
	cout << "fin" << endl;
	return 0;
}