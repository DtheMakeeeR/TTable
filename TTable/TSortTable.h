#pragma once
#include "TScanTable.h"
template<class TKey, class TVal>
class TSortTable : public TScanTable<TKey, TVal> {
private:
	void QSortRec(int s, int f);
public:
	TSortTable(int sz = 10) : TScanTable<TKey, TVal>(sz) {}
	TSortTable(const TScanTable<TKey, TVal>& t) : TScanTable<TKey, TVal>(t) { QSort(); }
	virtual bool Find(TKey k);
	virtual void Insert(TKey k, TVal v); 
	virtual void Insert(Record<TKey, TVal> rec);
	virtual void Delete(TKey k);
	void SelectSort();
	void QSort() { QSortRec(0, dataCount - 1); };
};

template<class TKey, class TVal>
void TSortTable<TKey, TVal>::QSortRec(int s, int f)
{
	if (s == f) return;
	int left = s, right = f;
	int index = (left + right) / 2;
	Record<TKey, TVal> k = pRec[index];
	while (left <= right) {
		while (pRec[left] < k) left++;
		while (k < pRec[right]) right--;
		if (left <= right) {
			Record<TKey, TVal> tmp = pRec[left];
			pRec[left] = pRec[right];
			pRec[right] = tmp;
			left++; right--;
		}
	}
	cout << endl << "s: " << s << " f: " << f << endl;
	cout << *this << endl;
	if (s < right ) QSortRec(s, right);
	if (left < f) QSortRec(left, f);
}

template<class TKey, class TVal>
bool TSortTable<TKey, TVal>::Find(TKey k)
{
	eff = 0;
	int s = 0, f = dataCount;
	while (s < f) {
		eff++;
		int ind = (s + f) / 2;
		if (pRec[ind].key > k) f = ind - 1;
		else if (pRec[ind].key < k) s = ind + 1;
		else {
			curr = ind;
			return true;
		}
	}
	curr = s;
	return false;
}

template<class TKey, class TVal>
void TSortTable<TKey, TVal>::Insert(TKey k, TVal v)
{
	if (dataCount == size) throw - 1;
	if (Find(k)) throw - 1;
	for (size_t i = dataCount; i > curr; i--) pRec[i] = pRec[i - 1]; 
	pRec[curr].key = k; pRec[curr].val = v;
	dataCount++;
}

template<class TKey, class TVal>
void TSortTable<TKey, TVal>::Insert(Record<TKey, TVal> rec)
{
	if (dataCount == size) throw - 1;
	if (Find(rec.key)) throw - 1;
	for (size_t i = dataCount; i > curr; i--) 
	{
		eff++;
		pRec[i] = pRec[i - 1];
	}
	pRec[curr] = rec;
	dataCount++;
}

template<class TKey, class TVal>
void TSortTable<TKey, TVal>::Delete(TKey k)
{
	if (dataCount == 0) throw - 1;
	if (!Find(k)) throw - 1;
	for (size_t i = curr; i < dataCount - 1; i++)
	{
		eff++;
		pRec[i] = pRec[i + 1];
	}
	dataCount--;
}

template<class TKey, class TVal>
void TSortTable<TKey, TVal>::SelectSort()
{
	int i = 0, j = 0;
	while (i < dataCount - 1) {
		j = i;
		int min = j;
		while (j < dataCount) {
			if (pRec[j].key < pRec[min].key) min = j;
			j++;
		}
		Record<TKey, TVal> tmp = pRec[min];
		pRec[min] = pRec[i];
		pRec[i] = tmp;
		i++;
	}
}
