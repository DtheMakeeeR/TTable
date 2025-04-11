#include "Model.h"

void Model::Update(string message)
{
    system("cls");
    cout << "Items count: " << tablesSize << endl;
    cout << "Errors: " << errCount << endl;
    cout << "Efficiencies: " << endl;
    cout << "ScanTable: " << tables[0]->GetEff() << endl;
    cout << "SortTable: " << tables[1]->GetEff() << endl;
    cout << "ArrayHashTable: " << tables[2]->GetEff() << endl;
    cout << "ListHashTable: " << tables[3]->GetEff() << endl;
    cout << "Choose operation:" << endl;
    cout << "1: Create tables(size, border)" << endl;
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
}

void Model::Find(int key)
{
    for (size_t i = 0; i < tableCount; i++)
    {
        tables[i]->Find(key);
    }
}

void Model::Delete(int key)
{
    for (size_t i = 0; i < tableCount; i++)
    {
        tables[i]->Delete(key);
    }
}

void Model::Clear()
{
    for (size_t i = 0; i < tableCount; i++)
    {
        tables[i]->Clear();
    }
}

void Model::InsertMany(int count, int border)
{
    int r;
    for (int i = 0; i < count; i++)
    {
        r = Random(border);
        try
        {
            Insert(r, i);
        }
        catch (...)
        {
            errCount++;
        }
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
    std::cout << "select sort eff: " << selectSort.GetEff() << std::endl;
    std::cout << "quick sort eff: " << quickSort.GetEff() << std::endl;
    std::cout << "merge sort eff: " << mergeSort.GetEff() << std::endl;
    cout << "Enter any button";
    char key;
    cin >> key;
}

void Model::CreateTables(int size, int border)
{
    if (size != tablesSize)
    {
        tablesSize = size;
        delete tables[0];
        delete tables[1];
        delete tables[2];
        delete tables[3];
        tables[0] = new TScanTable<int, int>(tablesSize);
        tables[1] = new TSortTable<int, int>(tablesSize);
        tables[2] = new ArrayHashTable<int, int>(tablesSize);
        tables[3] = new ListHashTable<int, int>(tablesSize);
    }
    else Clear();
    errCount = 0;
    int r;
    InsertMany(size, border);
}

void Model::FilesUpdate()
{
    vector<string> paths;
    paths.push_back("ScanTable.txt");
    paths.push_back("SortTable.txt");
    paths.push_back("ListHashTable.txt");
    paths.push_back("ArrayHashTable.txt");
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
}

int Model::Random(int border)
{
    return rand() % border;
}


Model::Model(int size) : tableCount(4)
{
    errCount = 0;
    tablesSize = size;
    tables = new TTable<int, int>* [tableCount];
    tables[0] = new TScanTable<int, int>(tablesSize);
    tables[1] = new TSortTable<int, int>(tablesSize);
    tables[2] = new ArrayHashTable<int, int>(tablesSize);
    tables[3] = new ListHashTable<int, int>(tablesSize);
}
void Model::Run()
{
    Update();
    char key = 'a';
    while (key != 'q') {
        cin >> key;
        int number1, number2;
        switch (key)
        {
        case '1':
            cin >> number1 >> number2;
            if (number1 < 1 || number2 < 1) Update("Only positive numbers");
            else
            {
                CreateTables(number1, number2);
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
                    Find(number1);
                    Update("Scanned");
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
