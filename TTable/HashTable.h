#pragma once
#include "TTable.h"
template <class TKey, class TVal>
class HashTable: public TTable<TKey, TVal>
{
protected:
	int size;
	virtual int HashFunc(TKey k);
public:
	HashTable(int sz = 10) {}
};

template<class TKey, class TVal>
int HashTable<TKey, TVal>::HashFunc(TKey k)
{
	eff += 1;
	return k % size;
}
