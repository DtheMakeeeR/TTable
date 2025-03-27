#include "TScanTable.h"
#include "TSortTable.h"
#include "ArrayHashTable.h"
void main() {
	ArrayHashTable<int, int> hashT(100);
	for (int i = 0; i < 30; i++)
	{
		hashT.Insert(i * 10, i);
	}
	cout << "*** hashT ***" << endl << hashT << endl;
	for (int i = 0; i < 10; i++)
	{
		hashT.Delete(i * 30);
	}
	cout << "*** hashT ***" << endl << hashT << endl;
}