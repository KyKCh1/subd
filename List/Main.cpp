#include "List.h"

using namespace std;

/*
* @brief Точка входа в программу. В ней представлен пример работы переопределённого оператора <<.
*/
int main() {

	List<int> l1;
	l1.pushBack(7);
	l1.pushBack(2);
	l1.pushBack(9);
	l1.popBack();
	l1.pushFront(0);
	l1.pushFront(-4);
	cout << l1;
	
	return 0;
}