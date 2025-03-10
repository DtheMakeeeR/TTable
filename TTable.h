#pragma once
#include "Record.h"
#include <iostream>
using namespace std;
template<class TKey, class TVal>
class TTable {
protected:
	int DataCount;
	int Eff;
public:
	//***************************** ŒÕ—“–” “Œ– » ƒ≈—“–” “Œ–
	TTable() :DataCount(0), Eff(0) {}
	virtual ~TTable() {}
	//*****************************—¬Œ…—“¬¿
	int GetDataCount() { return DataCount; }
	int GetEff() { return Eff; }
	//*****************************¿¡—“–¿ “Õ€≈
	bool IsEmpty() const { return DataCount == 0; }
	virtual	bool IsFull() const = 0;
	virtual bool Find(TKey key) = 0;
	virtual bool Insert(TKey key, TVal val) = 0;
	virtual bool Insert(Record<TKey, Tval> rec) = 0;
	virtual void Delete(TKey key) = 0;
	//*****************************»“≈–¿“Œ–
	virtual void Reset() = 0;
	virtual void GoNext() = 0;
	virtual bool IsEnd() = 0;
	virtual TKey GetCurrKey() = 0;
	virtual TVal GetCurrVal() = 0;
	virtual Record<TKey, TVal> GetCurrRec() = 0;
	friend ostream& operator<<(ostream& os, const TTable<TKey, TVal>& t);
};
template <class TKey, class TVal>
ostream& operator<<(ostream& os, const TTable<TKey, TVal>& t) {
	for (t.Reset(); !t.IsEnd(); t.GoNext()) {
		os << t.GetCurr() << endl;
		return os;
	}
}