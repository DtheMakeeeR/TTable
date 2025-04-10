#include <fstream>
#include <cstdlib>
#include "../TTable/ArrayHashTable.h"
#include "../TTable/ListHashTable.h"
#include "../TTable/TSortTable.h"
#include "../TTable/TArrayTable.h"
class Model
{
	TTable<int, int>* tables; 
	void Update(string message);
	void Insert(int key, int val);
	void Delete(int key);
	void CheckSorts();
	void CreateTables();
	void FileUpdate();
	int Random(int border);
public:
	void Run();
};