#pragma once
#include "TArrayTable.h"
template <class TKey, class TVal>
class TScanTable : public TArrayTable<TKey, TVal> {
public:
	TScanTable(int sz = 10) : TArrayTable<TKey, TVal>(sz) {}
	virtual bool Find(TKey k);
	virtual void Insert(TKey k, TVal v);
	virtual void Insert(Record<TKey, TVal> rec);
	virtual void Delete(TKey k);
};

template<class TKey, class TVal>
bool TScanTable<TKey, TVal>::Find(TKey k)
{
	eff = 0;
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
}

template<class TKey, class TVal>
void TScanTable<TKey, TVal>::Insert(Record<TKey, TVal> rec)
{
	if (dataCount == size) throw - 1;
	if (Find(rec.key)) throw - 1;
	pRec[curr] = rec;
	dataCount++;
}

template<class TKey, class TVal>
void TScanTable<TKey, TVal>::Delete(TKey k)
{
	if (Find(k)) this->pRec[this->curr] = this->pRec[(this->dataCount)--];
}
