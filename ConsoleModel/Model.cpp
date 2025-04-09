#include <fstream>
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
	int Random();
	void CreateTables();
	void FileUpdate();
public:
	void Run();
};