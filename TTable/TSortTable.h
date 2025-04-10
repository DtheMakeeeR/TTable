#pragma once
#include "TScanTable.h"
enum SortType {
	MergeSort,
	QuickSort,
	SelectSort
};
template<class TKey, class TVal>
class TSortTable : public TScanTable<TKey, TVal> {
private:
	Record<TKey, TVal>* tmpArr;
	void QSortRec(int s, int f);
	void Merge(int left, int mid, int right);
public:
	TSortTable(int sz = 10) : TScanTable<TKey, TVal>(sz) {}
	TSortTable(const TScanTable<TKey, TVal>& t, SortType type = QuickSort);
	virtual bool Find(TKey k);
	virtual void Insert(TKey k, TVal v); 
	virtual void Insert(Record<TKey, TVal> rec);
	virtual void Delete(TKey k);
	void SelectSort();
	void QSort() { QSortRec(0, dataCount - 1); };
	void MSort(int l, int r);
};

template<class TKey, class TVal>
void TSortTable<TKey, TVal>::QSortRec(int s, int f)
{
	if (s == f) return;
	int left = s, right = f;
	int index = (left + right) / 2;
	Record<TKey, TVal> k = pRec[index];
	while (left <= right) {
		while (pRec[left] < k)
		{
			eff++;
			left++;
		}
		while (k < pRec[right])
		{
			eff++;
			right--;
		}
		if (left <= right) {
			Record<TKey, TVal> tmp = pRec[left];
			pRec[left] = pRec[right];
			pRec[right] = tmp;
			left++; right--;
			eff++;
		}
	}
	if (s < right ) QSortRec(s, right);
	if (left < f) QSortRec(left, f);
}

template<class TKey, class TVal>
void TSortTable<TKey, TVal>::Merge(int left, int mid, int right)
{
	int i = left, j = mid + 1, k = left;
	while (i <= mid && j <= right)
	{
		if (pRec[i] < pRec[j]) tmpArr[k++] = pRec[i++];
		else tmpArr[k++] = pRec[j++];
		eff++;
	}
	if (i <= mid) while (i <= mid)
	{
		eff++;
		tmpArr[k++] = pRec[i++];
	}
	else while (j <= right) 
	{
		eff++;
		tmpArr[k++] = pRec[j++];
	}
	for (i = left; i <= right; i++) {
		eff++;
		pRec[i] = tmpArr[i];
	}
}

template<class TKey, class TVal>
TSortTable<TKey, TVal>::TSortTable(const TScanTable<TKey, TVal>& t, SortType type): TScanTable<TKey, TVal>(t)
{
	if (type == MergeSort)
	{
		tmpArr = new Record<TKey, TVal>[size];
		MSort(0, dataCount - 1);
		delete[] tmpArr;
	}
	else if (type == QuickSort) QSort();
	else SelectSort();
	tmpArr = nullptr;
}

template<class TKey, class TVal>
bool TSortTable<TKey, TVal>::Find(TKey k)
{
	eff = 0;
	int s = 0, f = dataCount-1;

	while (s <= f) {
		eff++;;
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
	eff = 0;
	int i = 0, j = 0;
	while (i < dataCount - 1) {
		j = i;
		int min = j;
		while (j < dataCount) {
			if (pRec[j].key < pRec[min].key) min = j;
			eff++;
			j++;
		}
		Record<TKey, TVal> tmp = pRec[min];
		pRec[min] = pRec[i];
		pRec[i] = tmp;
		i++;
	}
}

template<class TKey, class TVal>
void TSortTable<TKey, TVal>::MSort(int l, int r)
{
	if (l >= r) return;
	int m = (l + r) / 2;
	MSort(l, m);
	MSort(m + 1, r);
	Merge(l, m, r);
}
