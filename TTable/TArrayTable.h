#pragma once
#include "TTable.h"
template <class TKey, class TVal>
class TArrayTable : public TTable<TKey, TVal> {
protected:
	int size, curr;
	Record<TKey, TVal>* pRec;
public:
	TArrayTable(int sz = 10);
	TArrayTable(const TArrayTable<TKey, TVal>& t);

	TKey GetCurrKey() { return pRec[curr].key; }
	TVal GetCurrVal() { return pRec[curr].val; }
	Record<TKey, TVal> GetCurrRec() { return pRec[curr]; }

	void Clear() { dataCount = 0; }

	bool IsFull() const { return dataCount == size; }
	bool IsEmpty() { return dataCount == 0; }
	void Reset() { curr = 0; };
	void GoNext() { curr++; };
	bool IsEnd() { return curr == dataCount; }
	
	TArrayTable<TKey, TVal>& operator=(const TArrayTable<TKey, TVal>& t);

	~TArrayTable() { delete[] pRec; }
};

template<class TKey, class TVal>
TArrayTable<TKey, TVal>::TArrayTable(int sz) : TTable<TKey, TVal>()
{
	size = sz;
	pRec = new Record<TKey, TVal>[size];
	curr = -1;
}

template<class TKey, class TVal>
TArrayTable<TKey, TVal>::TArrayTable(const TArrayTable<TKey, TVal>& t)
{
	size = t.size;
	curr = t.curr;
	dataCount = t.dataCount;
	eff = t.eff;
	pRec = new Record<TKey, TVal>[size];
	for (int i = 0; i < size; i++)
	{
		pRec[i] = t.pRec[i];
	}
}

template<class TKey, class TVal>
TArrayTable<TKey, TVal>& TArrayTable<TKey, TVal>::operator=(const TArrayTable<TKey, TVal>& t)
{
	if (this == &t) return *this;
	if (size != t.size)
	{
		delete pRec;
		pRec = new Record<TKey, TVal>[size];
	}
	dataCount = t.dataCount;
	for (int i = 0; i < size; i++) pRec[i] = t.pRec[i];
	return *this;
}
