#include <filesystem>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <typeinfo>
#include "../TTable/ArrayHashTable.h"
#include "../TTable/ListHashTable.h"
#include "../TTable/TSortTable.h"
#include "../TTable/TArrayTable.h"
#include "../TTable/TreeTable.h"
#include "../TTable/TBalanceTreeTable.h"
#define tableCount 6
class Model
{
	int tablesSize;
	int tablesItems;
	int errCount;
	TTable<int, int>** tables; 
	void Update(string message = "", bool color = true);
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
	Model(int size = 100);
	void Run();

	~Model();
};