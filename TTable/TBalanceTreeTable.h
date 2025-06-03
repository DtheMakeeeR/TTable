#pragma once
#include "TreeTable.h"

const int H_OK = 0, H_INC = 1, H_DEC = -1;

template <typename TKey, typename TVal>
class TBalanceTreeTable : public TreeTable<TKey, TVal> {
protected:
    int InsBalTree(TreeNode<TKey, TVal>*& pNode, Record<TKey, TVal> rec);
    int BalTreeLeft(TreeNode<TKey, TVal>*& pNode, bool flag = true);
    int BalTreeRight(TreeNode<TKey, TVal>*& pNode, bool flag = true);
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
int TBalanceTreeTable<TKey, TVal>::BalTreeLeft(::TreeNode<TKey, TVal>*& pNode, bool flag = true) 
{
    int res = H_OK; 
    if (pNode->bal == 1) {
        pNode->bal = 0; 
        if (flag) res = H_OK;
        else res = H_DEC;
    }
    else if (pNode->bal == 0) { 
        pNode->bal = -1; 
        if (flag) res = H_INC;
        else res = H_OK;

    }
    
    else if (pNode->bal == -1) {
        ::TreeNode <TKey, TVal>* p1 = pNode->pLeft;
        if (p1->bal == -1) { 
            pNode->pLeft = p1->pRight;
            p1->pRight = pNode;
            pNode->bal = 0; 
            pNode = p1;
            pNode->bal = 0;
        }

        else { 
            ::TreeNode <TKey, TVal>* p2 = p1->pRight;
            p1->pRight = p2->pLeft;
            p2->pLeft = p1;
            pNode->pLeft = p2->pRight;
            p2->pRight = pNode;

            if (p2->bal == -1) { 
                pNode->bal = 1; 
            }
            else pNode->bal = 0; 

            if (p2->bal == 1) { 
                p1->bal = -1; 
            }

            else p1->bal = 0;

            pNode = p2;
            pNode->bal = 0;
            if (flag) res = H_OK;
            else res = H_DEC;
        }
    }
    return res;
}

template<typename TKey, typename TVal>
int TBalanceTreeTable<TKey, TVal>::BalTreeRight(::TreeNode<TKey, TVal>*& pNode, bool flag = true)
{
    int res = H_OK;
    if (pNode->bal == -1) {
        pNode->bal = 0;
        res = flag ? H_OK : H_DEC;
    }
    else if (pNode->bal == 0) {
        pNode->bal = 1;
        res = flag ? H_INC : H_OK;
    }
    else if (pNode->bal == 1) {
        ::TreeNode<TKey, TVal>* p1 = pNode->pRight;
        if (p1->bal == 1) {
            pNode->pRight = p1->pLeft;
            p1->pLeft = pNode;
            pNode->bal = 0;
            pNode = p1;
            pNode->bal = 0;
        }
        else {
            ::TreeNode<TKey, TVal>* p2 = p1->pLeft;
            p1->pLeft = p2->pRight;
            p2->pRight = p1;
            pNode->pRight = p2->pLeft;
            p2->pLeft = pNode;
            if (p2->bal == 1)        pNode->bal = -1;
            else                     pNode->bal = 0;
            if (p2->bal == -1)       p1->bal = 1;
            else                     p1->bal = 0;

            pNode = p2;
            pNode->bal = 0;
        }
        res = flag ? H_OK : H_DEC;
    }
    return res;
}

template<typename TKey, typename TVal>
int TBalanceTreeTable<TKey, TVal>::DeleteRec(TreeNode<TKey, TVal>*& pNode, TKey key)
{
    int res = H_OK;
    this->eff++;

    if (pNode == nullptr) {
        return res; // элемент не найден
    }
    else {
        if (pNode->rec.key < key) {
            int tmp = DeleteRec(pNode->pRight, key);
            if (tmp != H_OK) {
                res = BalTreeLeft(pNode, false); //второым параметром в BalTreeLeft надо передавать некий флаг (false) - когда она работает при вставке или при удалении (если передаем доп. флаг false, то балансировка работает при удалении, без флага - работает при вставке)
            }
        }
        else  if (pNode->rec.key > key) {
            int tmp = DeleteRec(pNode->pLeft, key);
            if (tmp != H_OK) {
                res = BalTreeRight(pNode, false); //+добавить параметр false;
            }
        }
        else {
            this->dataCount--;
            if (!pNode->pLeft || !pNode->pRight) {
                // 0 или 1 потомок
                ::TreeNode<TKey, TVal>* old = pNode;
                pNode = (pNode->pLeft) ? pNode->pLeft : pNode->pRight;
                delete old;
                return H_DEC;
            }
            else {
                //два потомка: находим min в правом поддереве
                ::TreeNode<TKey, TVal>* min = FindMin(pNode->pRight);
                pNode->rec = min->rec;
                int tmp = RemoveMin(pNode->pRight);
                if (tmp != H_OK) {
                    res = BalTreeLeft(pNode, false);
                }
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
