#pragma once
#include "TreeTable.h"

const int H_OK = 0, H_INC = 1, H_DEC = -1;

template <typename TKey, typename TVal>
class TBalanceTreeTable : public TreeTable<TKey, TVal> {
protected:
    int InsBalTree(TreeNode<TKey, TVal>*& pNode, Record<TKey, TVal> rec);
    int BalTreeLeft(TreeNode<TKey, TVal>*& pNode, bool isInsert = true);
    int BalTreeRight(TreeNode<TKey, TVal>*& pNode, bool isInsert = true);
    int DeleteRec(TreeNode<TKey, TVal>*& pNode, TKey key);
    TreeNode<TKey, TVal>* FindMin(TreeNode<TKey, TVal>* pNode);
    int RemoveMin(TreeNode<TKey, TVal>*& pNode);
public:
	TBalanceTreeTable() : TreeTable<TKey, TVal>() {};
	TBalanceTreeTable(const TBalanceTreeTable<TKey, TVal>& t) : TreeTable<TKey, TVal>(t) {};
    void Insert(Record<TKey, TVal> rec);
    void Insert(TKey key, TVal val);
    void Delete(TKey key);
	TBalanceTreeTable<TKey, TVal>& operator=(const TBalanceTreeTable<TKey, TVal>& other) {
		if (this != &other) {
			TreeTable<TKey, TVal>::operator=(other);
		}
		return *this;
	}
};
template <typename TKey, typename TVal>
int TBalanceTreeTable<TKey, TVal>:: InsBalTree(TreeNode<TKey, TVal>*& pNode, Record<TKey, TVal> rec) { //по ссылке корень тк он может измениться
    int res = H_OK;
    if (pNode == nullptr) {
        eff++;
        pNode = new TreeNode<TKey, TVal>(rec.key, rec.val);
        res = H_INC;
        dataCount++;
    }
    else if (rec.key < pNode->rec.key) {
        eff++;
        int tmp = InsBalTree(pNode->pLeft, rec);
        if (tmp == H_INC) {
            res = BalTreeLeft(pNode);
        }
    }
    else if (pNode->rec.key < rec.key) {
        eff++;
        int tmp = InsBalTree(pNode->pRight, rec);
        if (tmp == H_INC) {
            res = BalTreeRight(pNode);
        }
    }
    return res;
}

template <typename TKey, typename TVal>
int TBalanceTreeTable<TKey, TVal>::BalTreeLeft(TreeNode<TKey, TVal>*& pNode, bool isInsert)
{
    int res = H_OK;
    if (pNode->bal == BAL_RIGHT) {
        pNode->bal = BAL_OK;
        if (isInsert) res = H_OK;
        else res = H_DEC;
    }
    else if (pNode->bal == BAL_OK) {
        pNode->bal = BAL_LEFT;
        if (isInsert) res = H_INC;
        else res = H_OK;
    }
    else if (pNode->bal == BAL_LEFT) {
        TreeNode<TKey, TVal>* p1 = pNode->pLeft;
        if (p1->bal == BAL_LEFT) {
            pNode->pLeft = p1->pRight;
            p1->pRight = pNode;
            pNode->bal = BAL_OK;
            pNode = p1;
            pNode->bal = BAL_OK;
        }
        else {
            TreeNode<TKey, TVal>* p2 = p1->pRight;
            p1->pRight = p2->pLeft;
            p2->pLeft = p1;
            pNode->pLeft = p2->pRight;
            p2->pRight = pNode;
            if (p2->bal == BAL_LEFT) {
                pNode->bal = BAL_RIGHT;
            }
            else {
                pNode->bal = BAL_OK;
            }
            if (p2->bal == BAL_RIGHT) {
                pNode->bal = BAL_LEFT;
            }
            else {
                p1->bal = BAL_OK;
            }
            pNode = p2;
            pNode->bal = BAL_OK;
            if (isInsert) res = H_OK;
            else res = H_DEC;
        }
    }
    return res;
}

template<typename TKey, typename TVal>
int TBalanceTreeTable<TKey, TVal>::BalTreeRight(TreeNode<TKey, TVal>*& pNode, bool isInsert)
{
    int res = H_OK;
    if (pNode->bal == BAL_LEFT) {
        pNode->bal = BAL_OK;
        if (isInsert) res = H_OK;
        else res = H_DEC;
    }
    else if (pNode->bal == BAL_OK) {
        pNode->bal = BAL_RIGHT;
        if (isInsert) res = H_INC;
        else res = H_OK;
    }
    else if (pNode->bal == BAL_RIGHT) {
        TreeNode<TKey, TVal>* p1 = pNode->pRight;
        if (p1->bal == BAL_RIGHT) {
            pNode->pRight = p1->pLeft;
            p1->pLeft = pNode;
            pNode->bal = BAL_OK;
            pNode = p1;
            pNode->bal = BAL_OK;
        }
        else {
            TreeNode<TKey, TVal>* p2 = p1->pLeft;
            p1->pLeft = p2->pRight;
            p2->pRight = p1;
            pNode->pRight = p2->pLeft;
            p2->pLeft = pNode;
            if (p2->bal == BAL_RIGHT) {
                pNode->bal = BAL_LEFT;
            }
            else {
                pNode->bal = BAL_OK;
            }
            if (p2->bal == BAL_LEFT) {
                pNode->bal = BAL_RIGHT;
            }
            else {
                p1->bal = BAL_OK;
            }
            pNode = p2;
            pNode->bal = BAL_OK;
            if (!isInsert) res = H_DEC;
        }
    }
    return res;
}

template<typename TKey, typename TVal>
int TBalanceTreeTable<TKey, TVal>::DeleteRec(TreeNode<TKey, TVal>*& pNode, TKey key)
{
    int res = H_OK;
    eff++;
    if (pNode == nullptr) throw - 1;
    if (pNode->rec.key < key)
    {
        int tmp = DeleteRec(pNode->pRight, key);
        if (tmp != H_OK) res = BalTreeLeft(pNode, false);
    }
    else if (key < pNode->rec.key)
    {
        int tmp = DeleteRec(pNode->pLeft, key);
        if (tmp != H_OK) res = BalTreeRight(pNode, false);
    }
    else
    {
        dataCount--;
        if (pNode->pLeft == nullptr && pNode->pRight == nullptr)
        {
            delete pNode;
            pNode = nullptr;
            res = H_DEC;
        }
        else if (pNode->pLeft == nullptr)
        {
            pNode->rec = pNode->pRight->rec;
            delete pNode->pRight;
            pNode->pRight = nullptr;
            pNode->bal = BAL_OK;
        }
        else if (pNode->pRight == nullptr)
        {
            pNode->rec = pNode->pLeft->rec;
            delete pNode->pLeft;
            pNode->pLeft = nullptr;
            pNode->bal = BAL_OK;
        }
        else
        {
            TreeNode<TKey, TVal>* tmpLeft = pNode->pLeft;
            TreeNode<TKey, TVal>* tmpRight = pNode->pRight;
            TreeNode<TKey, TVal>* pMin = FindMin(tmpRight);
            pNode->rec = pMin->rec;
            res = RemoveMin(tmpRight);
            pNode->pLeft = tmpLeft;
            pNode->pRight = tmpRight;
            if (res != H_OK)
            {
                BalTreeLeft(pNode, false);
            }
        }
    }
    return res;
}

template<typename TKey, typename TVal>
TreeNode<TKey, TVal>* TBalanceTreeTable<TKey, TVal>::FindMin(TreeNode<TKey, TVal>* pNode)
{
    TreeNode<TKey, TVal>* res = pNode;
    while (res->pLeft != nullptr)
    {
        eff++;
        res = res->pLeft;
    }
    return res;
}

template<typename TKey, typename TVal>
int TBalanceTreeTable<TKey, TVal>::RemoveMin(TreeNode<TKey, TVal>*& pNode)
{
    eff++;
    int res = H_OK;
    if (pNode->pLeft == nullptr)
    {
        TreeNode<TKey, TVal>* tmp = pNode;
        pNode = pNode->pRight;
        delete tmp;
        res = H_DEC;
    }
    else
    {
        res = RemoveMin(pNode->pLeft);
        if (res != H_OK) res = BalTreeRight(pNode, false);
    }
    return res;
}

template<typename TKey, typename TVal>
void TBalanceTreeTable<TKey, TVal>::Insert(Record<TKey, TVal> rec)
{
    if (Find(rec.key)) {
        throw - 1;
    }
    InsBalTree(pRoot, rec);
}

template<typename TKey, typename TVal>
void TBalanceTreeTable<TKey, TVal>::Insert(TKey key, TVal val)
{
    if (Find(key)) {
        throw - 1;
    }
	Record<TKey, TVal> rec(key, val);
    InsBalTree(pRoot, rec);
}

template<typename TKey, typename TVal>
void TBalanceTreeTable<TKey, TVal>::Delete(TKey key)
{
    if (IsEmpty()) throw -1;
    DeleteRec(pRoot, key);
}
