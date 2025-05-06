#include "TScanTable.h"
#include "TSortTable.h"
#include "ArrayHashTable.h"
#include"ListHashTable.h"
#include"TreeTable.h"
#include "TBalanceTreeTable.h"
void main() {
	TBalanceTreeTable<int, std::string> table;
	table.Insert(Record<int, std::string>(9, "Lesha Tsydenov"));
	//std::cout << table.GetEff() << endl;
	table.Insert(Record<int, std::string>(2, "Namsarai Baltahinov"));
	//std::cout << table.GetEff() << endl;
	table.Insert(Record<int, std::string>(12222, "Namsarai Baltahinov"));
	//std::cout << table.GetEff() << endl;
	table.Insert(Record<int, std::string>(3, "Dorzhi Zandakov"));
	//std::cout << table.GetEff() << endl;
	table.Insert(Record<int, std::string>(-6, "Bato Batuevich"));
	//std::cout << table.GetEff() << endl;
	table.Insert(Record<int, std::string>(5, "Zhargal Shushkevich"));
	//std::cout << table.GetEff() << endl;

	//TSortTable<int, std::string> tableSort(table, SortType::MergeSort);
	//std::cout << table;
	table.PrintTree(cout);
	//table.Clear();
	table.PrintTree(cout);
	//std::cout << table;

	//ListHashTable<int, int> lht;
}