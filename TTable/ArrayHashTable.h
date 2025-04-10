#pragma once
#include "HashTable.h"
template <class TKey, class TVal>
class ArrayHashTable: public HashTable<TKey, TVal>
{
protected:
	Record<TKey, TVal>* pRec;
	int step, curr;
	Record<TKey, TVal> empty, deleted;
public:
	ArrayHashTable(int sz = 10);

	bool IsFull() const { return dataCount == size; }

	bool Find(TKey key); 
	void Insert(TKey key, TVal val);
	void Insert(Record<TKey, TVal> rec);
	void Delete(TKey key);
	void Clear();

	void Reset();
	void GoNext();
	bool IsEnd() { return curr == size; }

	TKey GetCurrKey() { return pRec[curr].key; };
	TVal GetCurrVal() { return pRec[curr].val; }
	Record<TKey, TVal> GetCurrRec() { return pRec[curr]; }
	~ArrayHashTable() { delete[] pRec; }

	ArrayHashTable<TKey, TVal>& operator=(const ArrayHashTable<TKey, TVal>& t);
};

template<class TKey, class TVal>
ArrayHashTable<TKey, TVal>& ArrayHashTable<TKey, TVal>::operator=(const ArrayHashTable<TKey, TVal>& t)
{
	if (this == &t) return *this;
	if (size != t.size)
	{
		delete pRec;
		pRec = new Record<TKey, TVal>[size];
	}
	dataCount = t.dataCount;
	for (int i = 0; i < size; i++) pRec[i] = t.pRec[i];
}
template<class TKey, class TVal>
ArrayHashTable<TKey, TVal>::ArrayHashTable(int sz) : HashTable<TKey, TVal>(sz)
{
	step = 1;
	for (int i = 2; i * i < size; i++) {
		if (sz % i != 0) 
		{
			step = i;
			break;
		}
	}
	curr = 0;
	empty.key = -1;
	deleted.key = -2;
	pRec = new Record<TKey, TVal>[sz];
	for (size_t i = 0; i < sz; i++)
	{
		pRec[i] = empty;
	}
}

template<class TKey, class TVal>
bool ArrayHashTable<TKey, TVal>::Find(TKey key)
{
	eff = 0;
	curr = HashFunc(key);
	int tmp = -1;
	for (size_t i = 0; i < size; i++)
	{
		eff++;
		if (pRec[curr] == empty) break;
		else if (pRec[curr] == deleted && tmp == -1) tmp = curr ;
		else if (pRec[curr].key == key) return true;
		curr = (curr + step)%size;
	}
	if (tmp != -1) curr = tmp;
	return false;
}

template<class TKey, class TVal>
void ArrayHashTable<TKey, TVal>::Insert(TKey key, TVal val)
{
	if (dataCount == size) throw - 1;
	eff = 0;
	if (Find(key)) throw - 1;
	Record<TKey, TVal> tmp(key, val);
	pRec[curr] = tmp;
	dataCount++;
}

template<class TKey, class TVal>
void ArrayHashTable<TKey, TVal>::Insert(Record<TKey, TVal> rec)
{
	eff = 0;
	if (Find(rec.key)) throw - 1;
	pRec[curr] = rec;
	dataCount++;
}

template<class TKey, class TVal>
void ArrayHashTable<TKey, TVal>::Delete(TKey key)
{
	eff = 0;
	if (!Find(key)) throw - 1;
	pRec[curr] = deleted;
	dataCount--;
}

template<class TKey, class TVal>
void ArrayHashTable<TKey, TVal>::Clear()
{
	dataCount = 0;
	for (int i = 0; i < size; i++) pRec[i] = empty;
}

template<class TKey, class TVal>
void ArrayHashTable<TKey, TVal>::Reset()
{
	curr = -1;
	GoNext();
}

template<class TKey, class TVal>
void ArrayHashTable<TKey, TVal>::GoNext()
{
	curr++;
	while ((pRec[curr] == empty || pRec[curr] == deleted) && !IsEnd()) curr++;
}
