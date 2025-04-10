#include <fstream>
#include <cstdlib>
#include "../TTable/ArrayHashTable.h"
#include "../TTable/ListHashTable.h"
#include "../TTable/TSortTable.h"
#include "../TTable/TArrayTable.h"
class Model
{
	int tableCount;
	int tablesSize;
	TTable<int, int>** tables; 
	void Update(string message);
	void Insert(int key, int val);
	void Delete(int key);
	void Clear();
	void CreateTables(int size, int border);
	void FileUpdate();
	int Random(int border);
public:
	void CheckSorts(int size, int border);
	Model(int size = 10);
	void Run();

	~Model();
};