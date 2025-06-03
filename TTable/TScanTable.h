#pragma once
#include "TArrayTable.h"
template <class TKey, class TVal>
class TScanTable : public TArrayTable<TKey, TVal> {
public:
	TScanTable(int sz = 10) : TArrayTable<TKey, TVal>(sz) {}
	TScanTable(const TScanTable<TKey, TVal>& t) : TArrayTable<TKey, TVal>(t) {}
	virtual bool Find(TKey k);
	virtual void Insert(TKey k, TVal v);
	virtual void Insert(Record<TKey, TVal> rec);
	virtual void Delete(TKey k);
	TScanTable<TKey, TVal>& operator=(const TScanTable<TKey, TVal> t);
};

template<class TKey, class TVal>
TScanTable<TKey, TVal>& TScanTable<TKey, TVal>:: operator=(const TScanTable<TKey, TVal> t)
{
	if (this == &t) return *this;
	TArrayTable<TKey, TVal>::operator=(t);
	return *this;
}
template<class TKey, class TVal>
bool TScanTable<TKey, TVal>::Find(TKey k)
{
	eff = 1;
	for (Reset(); !(IsEnd()); GoNext()) {
		eff++;
		if (GetCurrKey() == k) return true;
	}
	return false;
}

template<class TKey, class TVal>
void TScanTable<TKey, TVal>::Insert(TKey k, TVal v)
{
	if (dataCount == size) throw - 1;
	if (Find(k)) throw - 1;
	Record<TKey, TVal> r(k, v);
	pRec[curr] = r;
	dataCount++;
	eff++;
}

template<class TKey, class TVal>
void TScanTable<TKey, TVal>::Insert(Record<TKey, TVal> rec)
{
	if (dataCount == size) throw - 1;
	if (Find(rec.key)) throw - 1;
	pRec[curr] = rec;
	dataCount++;
	eff++;
}

template<class TKey, class TVal>
void TScanTable<TKey, TVal>::Delete(TKey k)
{
	if (!Find(k)) throw - 1;
	pRec[this->curr] = pRec[(this->dataCount-1)];
	dataCount--;
	eff++;
}
