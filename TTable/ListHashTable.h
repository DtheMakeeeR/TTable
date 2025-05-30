#pragma once
#include "HashTable.h"
#include <list>
#include <iterator>
template <class TKey, class TVal>
class ListHashTable : public HashTable<TKey, TVal>
{
protected:
	int currList;
	std::list <Record<TKey, TVal>>* pList;
	typename std::list<Record<TKey, TVal>>::iterator currI;
public:
	ListHashTable(int sz = 10);
	bool Find(TKey key);
	void Insert(TKey key, TVal val);
	void Insert(Record<TKey, TVal> rec);
	void Delete(TKey key);
	void Clear();

	bool IsFull() const;
	void Reset();
	void GoNext();
	bool IsEnd() { return currList >= size; }
	TKey GetCurrKey() { return currI->key; }
	TVal GetCurrVal() { return currI->val; }
	Record<TKey, TVal> GetCurrRec() { return *currI; }

	~ListHashTable() { delete[] pList; }

	ListHashTable<TKey, TVal>& operator=(const ListHashTable<TKey, TVal>& t);
};

template<class TKey, class TVal>
ListHashTable<TKey, TVal>::ListHashTable(int sz): HashTable<TKey, TVal>(sz)
{
	pList = new list <Record<TKey, TVal>>[size];
	currList = -1;
}

template<class TKey, class TVal>
bool ListHashTable<TKey, TVal>::Find(TKey key)
{
	eff = 0;
	currList = HashFunc(key);
	for (currI = pList[currList].begin(); currI != pList[currList].end(); currI++)
	{
		eff++;
		if (currI->key == key) return true;
	}
	return false;
}

template<class TKey, class TVal>
void ListHashTable<TKey, TVal>::Insert(TKey key, TVal val)
{
	if (Find(key)) throw - 1;
	Record<TKey, TVal> tmp(key, val);
	pList[currList].push_front(tmp);
	dataCount++;
	eff++;
}

template<class TKey, class TVal>
void ListHashTable<TKey, TVal>::Insert(Record<TKey, TVal> rec)
{
	if (dataCount == size - 1) throw - 1;
	if (Find(rec.key)) throw - 1;
	pList[currList].push_front(rec);
	dataCount++;
	eff++;
}

template<class TKey, class TVal>
void ListHashTable<TKey, TVal>::Delete(TKey key)
{
	if (dataCount == 0) throw - 1;
	if (!Find(key)) throw - 1;
	pList[currList].erase(currI);
	dataCount--;
	eff++;
}

template<class TKey, class TVal>
void ListHashTable<TKey, TVal>::Clear()
{
	dataCount = 0;
	for (int i = 0; i < size; i++) pList[i].clear();
}

template<class TKey, class TVal>
inline bool ListHashTable<TKey, TVal>::IsFull() const
{
	try
	{
		Record<TKey, TVal>* tmp = new Record<TKey, TVal>;
		delete tmp;
		return true;
	}
	catch (...)
	{
		return false;
	}
}

template<class TKey, class TVal>
void ListHashTable<TKey, TVal>::Reset()
{
	currList = 0;
	currI = pList[currList].begin();
	while (currI == pList[currList].end())
	{
		currList++;
		if (currList == size) break;
		currI = pList[currList].begin();
	}
}

template<class TKey, class TVal>
inline void ListHashTable<TKey, TVal>::GoNext()
{
	currI++;
	while (currI == pList[currList].end())
	{
		currList++;
		if (currList == size) break;
		currI = pList[currList].begin();
	}
}

template<class TKey, class TVal>
ListHashTable<TKey, TVal>& ListHashTable<TKey, TVal>::operator=(const ListHashTable<TKey, TVal>& t)
{
	if (this == &t) return *this;
	if (size != t.size)
	{
		delete[] pList;
		size = t.size;
		pList = new list<Record<TKey, TVal>>[size];
	}
	for (int i = 0; i < size; i++) pList[i].assign(t.pList[i].begin(), t.pList[i].end());
	dataCount = t.dataCount;
	return *this;
}