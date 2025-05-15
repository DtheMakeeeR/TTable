#include "TScanTable.h"
#include "TSortTable.h"
#include "ArrayHashTable.h"
#include"ListHashTable.h"
#include"TreeTable.h"
#include "TBalanceTreeTable.h"
void main() {
	/*TBalanceTreeTable<int, std::string> table;

	table.Insert(Record<int, std::string>(9, "Lesha Tsydenov"));
	table.Insert(Record<int, std::string>(2, "Namsarai Baltahinov"));
	table.Insert(Record<int, std::string>(12222, "Namsarai Baltahinov"));
	table.Insert(Record<int, std::string>(3, "Dorzhi Zandakov"));
	table.Insert(Record<int, std::string>(-6, "Bato Batuevich"));
	table.Insert(Record<int, std::string>(5, "Zhargal Shushkevich"));*/

	/*table.PrintTree(cout);
	table.PrintTree(cout);*/
	
	TBalanceTreeTable<int, int> test100;
	for (int i = 0; i < 20; i++) test100.Insert(i, i);
	test100.PrintTree(cout);
	for (int i = 0; i < 20; i++)
	{
		test100.Find(i);
		cout << i << "  " << test100.GetEff() << endl;
	}
	test100.Delete(15);
	test100.Delete(17);
	test100.Delete(5);
	test100.PrintTree(cout);
}