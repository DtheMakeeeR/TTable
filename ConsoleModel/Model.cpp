#include "Model.h"

void Model::Update(string message)
{
    system("cls");
    cout << "Tables sizes: " << tablesSize << endl;
    cout << "Items in tables: " << tablesItems << endl;
    cout << "Errors: " << errCount << endl;
    cout << "Efficiencies: " << endl;
    cout << "ScanTable: " << tables[0]->GetEff() << endl;
    cout << "SortTable: " << tables[1]->GetEff() << endl;
    cout << "ArrayHashTable: " << tables[2]->GetEff() << endl;
    cout << "ListHashTable: " << tables[3]->GetEff() << endl;
    cout << "TreeTable: " << tables[4]->GetEff() << endl;
    cout << "BalanceTreeTable: " << tables[5]->GetEff() << endl;
    cout << "Choose operation:" << endl;
    cout << "1: Create tables(size, count, border)" << endl;
    cout << "2: Insert item" << endl;
    cout << "3: Delete item" << endl;
    cout << "4: Find item" << endl;
    cout << "5: Insert MANY(count, border)" << endl;
    cout << "6: Clear tables" << endl;
    cout << "7: Check sorts(size, border)" << endl;
    cout << "q: Quit" << endl;
    if (message != "") {
        cout << "\033[31m" << message << "\033[0m" << endl;
    }
}

void Model::Insert(int key, int val)
{
    for (size_t i = 0; i < tableCount; i++)
    {
        tables[i]->Insert(key, val);
    }
    tablesItems++;
}

bool Model::Find(int key)
{
    bool res = true;
    for (size_t i = 0; i < tableCount; i++)
    {
        res = res&&(tables[i]->Find(key));
    }
    return res;
}

void Model::Delete(int key)
{
    for (size_t i = 0; i < tableCount; i++)
    {
        tables[i]->Delete(key);
    }
    tablesItems--;
}

void Model::Clear()
{
    for (size_t i = 0; i < tableCount; i++)
    {
        tables[i]->Clear();
    }
	tablesItems = 0;
}

void Model::InsertMany(int count, int border)
{
    int r, needToInsert = count;
	if (count > tablesSize - tablesItems) needToInsert = tablesSize - tablesItems;
	if (needToInsert > border) needToInsert = border;
    while(needToInsert > 0)
    {
        r = Random(border);
        try
        {
            Insert(r, r);
        }
        catch (...)
        {
            errCount++;
        }
		needToInsert--;
    }
}

void Model::CheckSorts(int size, int border)
{
    TScanTable<int, int> scan(size);
    int r;
    //errCount = 0;
    for (int i = 0; i < size; i++)
    {
        r = Random(border);
        try
        {
            scan.Insert(r, i);
        }
        catch (...)
        {
            errCount++;
        }
    }
    TSortTable<int, int> selectSort(scan, SortType::SelectSort);
    TSortTable<int, int> quickSort(scan, SortType::QuickSort);
    TSortTable<int, int> mergeSort(scan, SortType::MergeSort);
    TSortTable<int, int> insertSort;
    for (scan.Reset(); !scan.IsEnd(); scan.GoNext())
    {
        insertSort.Insert(scan.GetCurrRec());
    }
    std::cout << "select sort eff: " << selectSort.GetEff() << std::endl;
    std::cout << "quick sort eff: " << quickSort.GetEff() << std::endl;
    std::cout << "merge sort eff: " << mergeSort.GetEff() << std::endl;
    std::cout << "insert eff: " << mergeSort.GetEff() << std::endl;
    cout << "Enter any button";
    char key;
    cin >> key;
}

void Model::CreateTables(int size, int count, int border)
{
    if (size != tablesSize)
    {
        tablesSize = size;
        delete tables[0];
        delete tables[1];
        delete tables[2];
        delete tables[3];
		delete tables[4];
		delete tables[5];
        tables[0] = new TScanTable<int, int>(tablesSize);
        tables[1] = new TSortTable<int, int>(tablesSize);
        tables[2] = new ArrayHashTable<int, int>(tablesSize);
        tables[3] = new ListHashTable<int, int>(tablesSize);
		tables[4] = new TreeTable<int, int>();
		tables[5] = new TBalanceTreeTable<int, int>();
		tablesItems = 0;
    }
    else Clear();
    errCount = 0;
    InsertMany(count, border);
}

void Model::FilesUpdate()
{
    vector<string> paths;
    paths.push_back("ScanTable.txt");
    paths.push_back("SortTable.txt");
    paths.push_back("ListHashTable.txt");
    paths.push_back("ArrayHashTable.txt");
	paths.push_back("TreeTable.txt");
	paths.push_back("BalanceTreeTable.txt");
    for (size_t i = 0; i < paths.size(); i++)
    {
        ofstream out;
        out.open(paths[i]);
        if (out.is_open())
        {
            out << *tables[i];
        }
        out.close();
    }
    {
        ofstream out;
        out.open("PrintTreeTable.txt");
		if (out.is_open())
		{
			TreeTable<int, int>* tree = dynamic_cast<TreeTable<int, int>*>(tables[4]);
			tree->PrintTree(out);
		}
	}
    {
        ofstream out;
        out.open("PrintBalanceTreeTable.txt");
        if (out.is_open())
        {
            TBalanceTreeTable<int, int>* tree = dynamic_cast<TBalanceTreeTable<int, int>*>(tables[5]);
            tree->PrintTree(out);
        }
    }
}

int Model::Random(int border)
{
    return rand() % border;
}


Model::Model(int size)
{
    errCount = 0;
    tablesSize = size;
    tablesItems = 0;
    tables = new TTable<int, int>* [tableCount];
    tables[0] = new TScanTable<int, int>(tablesSize);
    tables[1] = new TSortTable<int, int>(tablesSize);
    tables[2] = new ArrayHashTable<int, int>(tablesSize);
    tables[3] = new ListHashTable<int, int>(tablesSize);
	tables[4] = new TreeTable<int, int>();
    tables[5] = new TBalanceTreeTable<int, int>();
}
void Model::Run()
{
    Update();
    char key = 'a';
    while (key != 'q') {
        cin >> key;
        int number1, number2, number3;
        switch (key)
        {
        case '1':
            cin >> number1 >> number2 >> number3;
            if (number1 < 1 || number2 < 1 || number3 < 1) Update("Only positive numbers");
            else
            {
                CreateTables(number1, number2, number3);
                Update("Created");
            }
            break;
        case '2':
            cin >> number1 >> number2;
            if (number1 < 1 || number2 < 1) Update("Only positive numbers");
            else
            {
                try
                {
                    Insert(number1, number2);
                    Update("Inserted");
                }
                catch (...)
                {
                    Update("Error occuried");
                }
            }
            break;
        case '3':
            cin >> number1;
            if (number1 < 1) Update("Only positive numbers");
            else
            {
                try
                {
                    Delete(number1);
                    Update("Deleted");
                }
                catch (...)
                {
                    Update("Error occuried");
                }
            }
            break;
        case '4':
            cin >> number1;
            if (number1 < 1) Update("Only positive numbers");
            else
            {
                try
                {
                    if (Find(number1))
                    {
                        Update("Founded");
                    }
                    else Update("Isnt founded");
                }
                catch (...)
                {
                    Update("Error occuried");
                }
            }
            break;
        case '5':
            cin >> number1 >> number2;
            if (number1 < 1 || number2 < 1) Update("Only positive numbers");
            else
            {
                InsertMany(number1, number2);
                Update("Inserted");
            }
            break;
        case '6':
            Clear();
            Update("Cleared");
            break;
        case '7':
            cin >> number1 >> number2;
            if (number1 < 1 || number2 < 1) Update("Only positive numbers");
            else
            {
                CheckSorts(number1, number2);
                Update("Checked");
            }
            break;
        case 'q':
            Update("Its all over...");
            break;
        default:
            Update("Try again");
            break;
        }
        FilesUpdate();
    }
    cin >> key;
}

Model::~Model()
{
    for (int i = 0; i < tableCount; i++) delete tables[i];
    delete[] tables;
}
