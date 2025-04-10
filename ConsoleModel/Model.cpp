#include "Model.h"

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
