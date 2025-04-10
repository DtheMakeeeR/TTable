#pragma once
#include "Record.h"
#include <iostream>
template <class TKey, class TVal>
class TTable {
protected:
	int dataCount;
	int eff;
public:
	//***************************** ŒÕ—“–” “Œ– » ƒ≈—“–” “Œ–
	TTable() :dataCount(0), eff(0) {}
	virtual ~TTable() {}
	//*****************************—¬Œ…—“¬¿
	int GetDataCount() { return dataCount; }
	int GetEff() { return eff; }
	//*****************************¿¡—“–¿ “Õ€≈
	bool IsEmpty() const { return dataCount == 0; }
	virtual	bool IsFull() const = 0;
	virtual bool Find(TKey key) = 0;
	virtual void Insert(TKey key, TVal val) = 0;
	virtual void Insert(Record<TKey, TVal> rec) = 0;
	virtual void Delete(TKey key) = 0;
	virtual void Clear() = 0;
	//*****************************»“≈–¿“Œ–
	virtual void Reset() = 0;
	virtual void GoNext() = 0;
	virtual bool IsEnd() = 0;
	virtual TKey GetCurrKey() = 0;
	virtual TVal GetCurrVal() = 0;
	virtual Record<TKey, TVal> GetCurrRec() = 0;
	friend ostream& operator<<(ostream& out, const TTable<TKey, TVal>& t);
};
template <class TKey, class TVal>
ostream& operator<<(ostream& out, TTable<TKey, TVal>& t) {
	out << "key - val" << endl;
	for (t.Reset(); !t.IsEnd(); t.GoNext()) {
		out << t.GetCurrKey() << " - " << t.GetCurrVal() << endl;
	}
	return out;
}