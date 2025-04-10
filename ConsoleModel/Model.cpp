#include "Model.h"

void Model::Insert(int key, int val)
{
    for (size_t i = 0; i < tableCount; i++)
    {
        tables[i]->Insert(key, val);
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

void Model::CheckSorts(int size, int border)
{
    TScanTable<int, int> scan(size);
    int r, errCount = 0;
    for (int i = 0; i < size; i++)
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
    TSortTable<int, int> selectSort(scan, SortType::SelectSort);
    TSortTable<int, int> quickSort(scan, SortType::QuickSort);
    TSortTable<int, int> mergeSort(scan, SortType::MergeSort);
    std::cout << "select sort eff: " << selectSort.GetEff() << std::endl;
    std::cout << "quick sort eff: " << quickSort.GetEff() << std::endl;
    std::cout << "merge sort eff: " << mergeSort.GetEff() << std::endl;
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
    int r, errCount = 0;
    for (int i = 0; i < tablesSize; i++)
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

int Model::Random(int border)
{
    return rand() % border;
}

Model::Model(int size) : tableCount(4)
{
    tablesSize = size;
    tables = new TTable<int, int>* [tableCount];
    tables[0] = new TScanTable<int, int>(tablesSize);
    tables[1] = new TSortTable<int, int>(tablesSize);
    tables[2] = new ArrayHashTable<int, int>(tablesSize);
    tables[3] = new ListHashTable<int, int>(tablesSize);
}

Model::~Model()
{
    for (int i = 0; i < tableCount; i++) delete tables[i];
    delete[] tables;
}
