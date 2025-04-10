#include "TScanTable.h"
#include "TSortTable.h"
#include "ArrayHashTable.h"
#include"ListHashTable.h"
void main() {
	/*TScanTable<int, int> scanT(10);
	scanT.Insert(50);
	scanT.Insert(40);
	scanT.Insert(45);
	scanT.Insert(-2);
	scanT.Insert(-1000);
	TSortTable<int, int> sortT = scanT;
	cout << sortT;*/
	TScanTable<int, std::string> table(10);
	table.Insert(Record<int, std::string>(9, "Lesha Tsydenov"));
	std::cout << table.GetEff() << endl;
	table.Insert(Record<int, std::string>(2, "Namsarai Baltahinov"));
	std::cout << table.GetEff() << endl;
	table.Insert(Record<int, std::string>(12, "Namsarai Baltahinov"));
	std::cout << table.GetEff() << endl;
	table.Insert(Record<int, std::string>(3, "Dorzhi Zandakov"));
	std::cout << table.GetEff() << endl;
	table.Insert(Record<int, std::string>(6, "Bato Batuevich"));
	std::cout << table.GetEff() << endl;
	table.Insert(Record<int, std::string>(5, "Zhargal Shushkevich"));
	std::cout << table.GetEff() << endl;

	//TSortTable<int, std::string> tableSort(table, SortType::MergeSort);
	std::cout << table;
	//ListHashTable<int, int> lht;
}