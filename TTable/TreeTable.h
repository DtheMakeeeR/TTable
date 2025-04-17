#pragma once
#include "Record.h"
#include "TTable.h"
#include <stack>
template <class TKey, class TVal>
struct TreeNode
{
	Record<TKey, TVal> rec;
	TreeNode* pLeft, *pRight;
	int bal;
public:
	TreeNode(TKey k, TVal v) : rec(k, v) {}
};
template <class TKey, class TVal>
class TreeTable : public TTable<TKey, TVal>
{
protected:
	TreeNode* pRoot, * pCurr, * pPrev;
	std::stack<TreeNode*> st;
public:
	TreeTable() : pRoot(nullptr), pCurr(nullptr), pPrev(nullptr) {};
	bool Find(TKey key);
	void Insert(TKey key, TVal val);
	void Insert(TRecord<TKey, TVal> rec);
};

template<class TKey, class TVal>
bool TreeTable<TKey, TVal>::Find(TKey key)
{
	eff = 0;
    pCurr = pRoot;
    while (pCurr != nullptr) {
        eff++;
        if (key > pCurr->rec.key) {
            pPrev = pCurr;
            pCurr = pCurr->pRight;
        }
        else if (key < pCurr->rec.key) {
            pPrev = pCurr;
            pCurr = pCurr->pLeft;
        }
        else if (key == pCurr->rec.key) {
            return true;
        }
    }
    eff++;
    pCurr = pPrev;
    return false;
}

template<class TKey, class TVal>
void TreeTable<TKey, TVal>::Insert(TKey key, TVal val)
{
    if (Find(key)) throw - 1;
    TreeNode<Tkey, Tval>* tmp(key, val);
    if (pCurr == nullptr) {
        pRoot = tmp;
    }
    else if (key > pCurr->rec.key) {
        pCurr->pRight = tmp;
    }
    else if (key < pCurr->rec.key) {
        pCurr->pLeft = tmp;
    }
    eff++;
    dataCount++;
    return false;
}

template<class TKey, class TVal>
inline void TreeTable<TKey, TVal>::Insert(TRecord<TKey, TVal> rec)
{
    if (Find(rec.key)) {
        throw - 1;
    }
    TreeNode<Tkey, Tval>* tmp = new TreeNode<TKey, TVal>(rec.key, rec.val);
    if (pCurr == nullptr) {
        pRoot = tmp;
    }
    else if (rec.key > pCurr->rec.key) {
        pCurr->pRight = tmp;
    }
    else if (rec.key < pCurr->rec.key) {
        pCurr->pLeft = tmp;
    }
    eff++;
    dataCount++;
}
