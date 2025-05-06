#include <filesystem>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <typeinfo>
#include "../TTable/ArrayHashTable.h"
#include "../TTable/ListHashTable.h"
#include "../TTable/TSortTable.h"
#include "../TTable/TArrayTable.h"
class Model
{
	int tableCount;
	int tablesSize;
	int tablesItems;
	int errCount;
	TTable<int, int>** tables; 
	void Update(string message = "");
	void Insert(int key, int val);
	bool Find(int key);
	void Delete(int key);
	void Clear();
	void InsertMany(int count, int border);
	void CreateTables(int size, int count, int border);
	void FilesUpdate();
	int Random(int border);
	void CheckSorts(int size, int border);
public:
	Model(int size = 10);
	void Run();

	~Model();
};