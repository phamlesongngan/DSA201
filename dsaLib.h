/*
 * =========================================================================================
 * Name        : dsaLib.h
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - Bach Khoa University
 * Description : Library for Assignment 2 - Data structures and Algorithms - Spring 2018
 * =========================================================================================
 */

#ifndef A02_DSALIB_H
#define A02_DSALIB_H

#include <string>
#include <math.h>
#include <vector>
#include<functional>

using namespace std;


class DSAException {
    int     _error;
    string  _text;
public:

    DSAException() : _error(0), _text("Success") {}
    DSAException(int err) : _error(err), _text("Unknown Error") {}
    DSAException(int err, const char* text) : _error(err), _text(text) {}

int getError() { return _error; }
string& getErrorText() { return _text; }
};

template <class T>
class List {
public:
	
	virtual void    clean() = 0;
	virtual void    clone(void*) = 0;
	virtual bool    isEmpty() = 0;
	virtual size_t  getSize() = 0;
	virtual T&      at(int i) = 0;
	virtual T&      operator[](int i) = 0;

	virtual bool    find(T& a, int& idx) = 0;
	virtual T*      find(T& a) = 0;
	virtual T*      find(T& a, std::function<bool(T&, T&)> eqCmp) = 0;
	virtual int     insert(int i, T& a) = 0;
	virtual int     insert(int i, T&& a) = 0;
	virtual int     remove(int i) = 0;
	virtual int     remove(T& a, std::function<bool(T&, T&)> eqCmp) = 0;

	virtual int     push_back(T& a) = 0;
	virtual int     push_back(T&& a) = 0;
	virtual int     insertHead(T& a) = 0;
	virtual int     insertHead(T&& a) = 0;
	virtual int     removeHead() = 0;
	virtual int     removeLast() = 0;

	virtual void    traverse(std::function<void(T&)> op) = 0;
	virtual void    traverse(std::function<void(T&, void*)> op, void* pParam) = 0;

	virtual void    reverse() = 0;
};

template <class T>
struct L1Item {
	T data;
	L1Item<T> *pNext;

	L1Item(T &a) : data(a), pNext(NULL) {}
	L1Item(T &a, void* next) : data(a), pNext(next) {}
	L1Item(T &&a) : data(std::move(a)), pNext(NULL) {}
	L1Item(T &&a, void* next) : data(std::move(a)), pNext(next) {}
};

template <class T>
class L1List : public List<T> {
	L1Item<T>   *_pHead;
	L1Item<T>	*_pCurrent;
	size_t      _size;
public:
	L1List() : _pHead(NULL), _size(0), _pCurrent(NULL) {}
	~L1List(){}
	void	currentuse(){ _pCurrent = _pHead; };
	void    clean();
	void    clone(void*);
	bool    isEmpty() { return _pHead == NULL; }
	size_t  getSize() { return _size; }

	T&      at(int i);
	T&      operator[](int i);
	bool	storeCur(T &current);
	bool    find(T& a, int& idx);
	T*      find(T& a);
	T*      find(T& a, std::function<bool(T&, T&)> eqCmp);//bool (*eqCmp)(T&, T&));
	int     insert(int i, T& a);
	int     insert(int i, T&& a);
	//int		insert(T& a, std::function<bool(T&, T&)> eqCmp);
	int     remove(int i);
	int     remove(T& a, std::function<bool(T&, T&)> eqCmp);

	int     push_back(T& a);
	int     push_back(T&& a);
	int     insertHead(T& a);
	int     insertHead(T&& a);
	int     removeHead();
	int     removeLast();
	//int		eqCmp(T* &a, T* &b);
	void    reverse() {
		if (isEmpty())
			return;
		L1Item<T>* p = NULL;
		L1Item<T>* ptr;
		while (_pHead != NULL) {
			ptr = _pHead;
			_pHead = _pHead->pNext;
			ptr->pNext = p;
			p = ptr;
		}
		_pHead = p;
	}

	void    traverse(std::function<void(T&)> op) {
		L1Item<T>   *p = _pHead;
		while (p) {
			op(p->data);
			p = p->pNext;
		}
	}
	//void    traverse(void (*op)(T&, void*), void* pParam) {
	void    traverse(std::function<void(T&, void*)> op, void* pParam) {
		L1Item<T>   *p = _pHead;
		while (p) {
			op(p->data, pParam);
			p = p->pNext;
		}
	}
};
template<class T>
bool L1List<T>::storeCur(T &current) {
	if (_pCurrent == NULL)
		return false;
	else {
		current = _pCurrent->data;
		_pCurrent = _pCurrent->pNext;
	}
	return true;
}
template <class T>
void L1List<T>::clean() {
	if (_pHead == NULL)
		return;
	L1Item<T>* p = _pHead;
	while (p != NULL) {
		_pHead = _pHead->pNext;
		delete p;
		p = _pHead;
	}
	_size = 0;
}
template <class T>
void L1List<T>::clone(void* pR) {
	L1List<T>* p = (L1List<T>*) pR;
	L1Item<T>* cur = this->_pHead;
	while (cur) {
		p->push_back(cur->data);
		cur = cur->pNext; 
		this->_size--;
	}
}
template <class T>
T& L1List<T>::at(int i) {
	if (this->_pHead != NULL) {
		L1Item<T> * pRet = this->_pHead;
		int idx = 0;
		while (pRet) {
			if (i != idx) {
				pRet = pRet->pNext;
				idx++;
			}
			else  return (pRet->data);
		}
	}
	T ret;
	return ret;
}

template <class T>
T& L1List<T>::operator[](int i) {
	return at(i);
}
template <class T>
bool L1List<T>::find(T& a, int& idx) {
	L1Item<T> * current = this->_pHead;
	while (current) {
		if (a == current->data) {
			return true;
		}
		idx++;
		current = current->pNext;
	}
	return false;
}
template <class T>
T*  L1List<T>::find(T& a) {
	L1Item<T> * current = this->_pHead;
	while (current) {
		if (a == current->data) {
			return &current->data;
		}
		current = current->pNext;
	}
}
template <class T>
T*  L1List<T>::find(T& a, std::function<bool(T&, T&)> eqCmp) {
	L1Item<T> * current = this->_pHead;
	while (current) {
		if (eqCmp(a, current->data)) {
			return &current->data;
		}
		current = current->pNext;
	}
}
template <class T>
int L1List<T>::insert(int i, T& a) {
	L1Item<T> * current = this->_pHead;
	int idx = 0;
	while (current) {
		if (i == idx) {
			break;
		}
		current = current->pNext;
		idx++;
	}
	L1Item<T> * pNew = new L1Item<T>(a);
	pNew->pNext = current->pNext;
	current->pNext = pNew;
	this->_size++;
	return idx;
}
template <class T>
int L1List<T>::insert(int i, T&& a) {
	L1Item<T> * current = this->_pHead;
	int idx = 0;
	while (current) {
		if (i == idx) {
			break;
		}
		current = current->pNext;
		idx++;
	}
	L1Item<T> * pNew = new L1Item<T>(std::move(a));
	pNew->pNext = current->pNext;
	current->pNext = pNew;
	this->_size++;
	return idx;
}


template <class T>
int L1List<T>::remove(int i) {
	if (!(isEmpty()) && (i > 0) && (i < (int)_size)) {
		L1Item<T>* p = _pHead;
		L1Item<T>* ptr = NULL;
		for (int count = 0; count < i - 1; count++)
			p = p->pNext;
		ptr = ptr->pNext;
		p->pNext = ptr->pNext;
		delete ptr;
		return 0;
	}
	else return -1;
}
template <class T>
int L1List<T>::remove(T& a, std::function<bool(T&, T&)> eqCmp) {
	if (eqCmp(a, this->_pHead->data)) {
		L1Item<T> * current = this->_pHead;
		this->_pHead = this->_pHead->pNext;
		this->_size--;
		delete current;
	}
	else {
		L1Item<T> * current = this->_pHead;
		L1Item<T> * preCurrent = NULL;
		this->_size--;
		while (current) {
			if (eqCmp(a, current->data)) {
				break;
			}
			preCurrent = current;
			current = current->pNext;
		}
		if (current) {
			preCurrent->pNext = current->pNext;
			current = NULL;
		}
	}
	return 0;
}
/// Insert item to the end of the list
/// Return 0 if success
template <class T>
int L1List<T>::push_back(T &a) {
	if (_pHead == NULL) {
		_pHead = new L1Item<T>(a);
	}
	else {
		L1Item<T>   *p = _pHead;
		while (p->pNext) p = p->pNext;
		p->pNext = new L1Item<T>(a);
	}

	_size++;
	return 0;
}

template <class T>
int L1List<T>::push_back(T &&a) {
	if (_pHead == NULL) {
		_pHead = new L1Item<T>(std::move(a));
	}
	else {
		L1Item<T>   *p = _pHead;
		while (p->pNext) p = p->pNext;
		p->pNext = new L1Item<T>(std::move(a));
	}

	_size++;
	return 0;
}

/// Insert item to the front of the list
/// Return 0 if success
template <class T>
int L1List<T>::insertHead(T &a) {
	L1Item<T>   *p = new L1Item<T>(a);
	p->pNext = _pHead;
	_pHead = p;
	_size++;
	return 0;
}

template <class T>
int L1List<T>::insertHead(T&& a) {
	L1Item<T>   *p = new L1Item<T>(std::move(a));
	p->pNext = _pHead;
	_pHead = p;
	_size++;
	return 0;
}

/// Remove the first item of the list
/// Return 0 if success
template <class T>
int L1List<T>::removeHead() {
	if (_pHead) {
		L1Item<T>* p = _pHead;
		_pHead = p->pNext;
		delete p;
		_size--;
		return 0;
	}
	return -1;
}

/// Remove the last item of the list
/// Return 0 if success
template <class T>
int L1List<T>::removeLast() {
	if (_pHead) {
		if (_pHead->pNext) {
			L1Item<T>* prev = _pHead;
			L1Item<T>* pcur = prev->pNext;
			while (pcur->pNext) {
				prev = pcur;
				pcur = pcur->pNext;
			}
			delete pcur;
			prev->pNext = NULL;
		}
		else {
			delete _pHead;
			_pHead = NULL;
		}
		_size--;
		return 0;
	}
	return -1;
}

int eqCmp(L1List<VRecord> &a, L1List<VRecord> &b) {
	int ret;
	ret = strcmp((a)[0].id, (b)[0].id);
	if (ret < 0)
		return -1;	//a < b
	else if (ret = 0)
		return 0;	//a = b
	else return 1;	//a > b
}
/************************************************************************
 * This section is for AVL tree
 ************************************************************************/
template <class T>
struct AVLNode {
    T           _data;
    AVLNode<T>   *_pLeft, *_pRight;
#ifdef AVL_USE_HEIGHT
    int         _height;
    AVLNode(T &a) : _data(a), _pLeft(NULL), _pRight(NULL), _height(1) {}
#else
    int         _bFactor;
    AVLNode(T &a) : _data(a), _pLeft(NULL), _pRight(NULL), _bFactor(0) {}
#endif
};


template <class T>
class AVLTree {
    AVLNode<T> *_pRoot;
	int(*eqcmp)(T&, T&);
public:
    AVLTree() : _pRoot(NULL) {}
    ~AVLTree() { destroy(_pRoot); }

	bool find(T& key, T* &ret, int(*eqcmp)(T&, T&)) { this->eqcmp = eqcmp; return find(_pRoot, key, ret); }
    bool insert(T& key, int(*eqcmp)(T&, T&)) { this->eqcmp = eqcmp; return insert(_pRoot, key); }
    bool remove(T& key, int(*eqcmp)(T&, T&)) { this->eqcmp = eqcmp; return remove(_pRoot, key); }
    void traverseNLR(void (*op)(T&)) { traverseNLR(_pRoot, op); }
    void traverseLNR(void (*op)(T&)) { traverseLNR(_pRoot, op); }
    void traverseLRN(void (*op)(T&)) { traverseLRN(_pRoot, op); }

protected:
	
    void destroy(AVLNode<T>* &pR);
    bool find(AVLNode<T> *pR, T& key, T* &ret);
    bool insert(AVLNode<T>* &pR, T& a);
    bool remove(AVLNode<T>* &pR, T& a);
    void traverseNLR(AVLNode<T> *pR, void (*op)(T&));
    void traverseLNR(AVLNode<T> *pR, void (*op)(T&));
    void traverseLRN(AVLNode<T> *pR, void (*op)(T&));

    void rotLeft(AVLNode<T>* &pR);
    void rotRight(AVLNode<T>* &pR);
    void rotLR(AVLNode<T>* &pR);
    void rotRL(AVLNode<T>* &pR);

    bool balanceLeft(AVLNode<T>* &pR);
    bool balanceRight(AVLNode<T>* &pR);
};
template<class T>
void AVLTree<T>::destroy(AVLNode<T>* &pR) {
	if (pR) {
		destroy(pR->_pLeft);
		destroy(pR->_pRight);
		delete pR;
	}
}
template<class T>
bool AVLTree<T>::find(AVLNode<T> *pR, T& key, T* &ret) {
	bool found = false;
	AVLNode<T>* ptr = _pRoot;
	while (!found && ptr != NULL) {
		if(eqcmp(key, ptr->data) < 0)
			ptr = ptr->_pLeft;
		if(eqcmp(key, ptr->data) > 0)
			ptr = ptr->_pRight;
		else{
			ret = ptr;
			return true;
		}
	}
	return false;
}
template<class T>
bool AVLTree<T>::insert(AVLNode<T>* &pR, T& a) {
	//pR = new AVLNode<T>(a);
	if (pR == NULL) {
		pR = new AVLNode<T>(a);
		return true;
	}
	bool balance;
	if (eqcmp(key, ptr->data) < 0) {
		balance = insert(pR->_pLeft, a);
		if (balance) {
			if (pR->_bFactor == -1)
				balance = balanceLeft(pR);
			else if (pR->_bFactor == 0)
				pR->_bFactor = -1;
			else {
				pR->_bFactor = 0;
				balance = false;
			}
		}
	}
	else {
		balance = insert(pR->_pRight, a);
		if (balance) {
			if (pR->_bFactor == -1) { 
				pR->_bFactor = 0;
				balance = false;
			}
			else if (pR->_bFactor == 0)
				pR->_bFactor = 1;
			else {
				balance = balanceRight(pR);
			}
		}
	}
	return balance;
}
template<class T>
bool AVLTree<T>::remove(AVLNode<T>* &pR, T& a) {
	if (pR == NULL)
		return false;
	bool removal = true;
	if (eqcmp(key, ptr->data) < 0) {
		removal = remove(pR->_pLeft, a);
		if (removal) {
			if (pR->_bFactor == 1) {
				removal = !balanceRight(pR);
			}
			else if (pR->_bFactor == 0) {
				pR->_bFactor = 1;
				removal = false;
			}
			else 
				pR->_bFactor = 0;
		}
	}
	else if (eqcmp(key, ptr->data) > 0) {
		pR->_pRight = remove(pR->_pRight, a);
		if (removal) {
			if (pR->_bFactor == -1) {
				removal = !balanceLeft(pR);
			}
			else if (pR->_bFactor == 0) {
				pR->_bFactor = -1;
				removal = false;
			}
			else
				pR->_bFactor = 0;
		}
	}
	else {
		if ((pR->_pLeft == NULL) || (pR->_pRight == NULL)) {
			AVLNode<T>* tmp = pR->_pLeft ? pR->_pLeft : pR->_pRight;
			if (tmp == NULL) {
				tmp = pR;
				pR = NULL;
			}
			else
				*pR = *tmp
				delete (tmp);
		}
		else {
			AVLNode<T>* tmp = pR;
			pR->_data = tmp->_data;
			pR->_pRight = remove(pR->_pRight, tmp->_data);
		}
	}
}
template<class T>
void AVLTree<T>::traverseNLR(AVLNode<T> *pR, void(*op)(T&)) {
	if (pR) {
		cout <<pR->_data<< " ";
		traverseNLR(pR->_pLeft);
		traverseNLR(pR->_pRight);
	}
}
template<class T>
void AVLTree<T>::traverseLNR(AVLNode<T> *pR, void(*op)(T&)) {
	if (pR) {
		traverseLNR(pR->_pLeft);
		cout << pR->_data << " ";
		traverseLNR(pR->_pRight);
	}
}
template<class T>
void AVLTree<T>::traverseLRN(AVLNode<T> *pR, void(*op)(T&)) {
	if (pR) {
		traverseLRN(pR->_pLeft);
		traverseLRN(pR->_pRight);
		cout << pR->_data << " ";
	}
}
template<class T>
void AVLTree<T>::rotLeft(AVLNode<T>* &pR) {
	AVLNode<T>* &ptr = pR->_pRight;
	pR->_pLeft;
	ptr->_pLeft;
}
template<class T>
void AVLTree<T>::rotRight(AVLNode<T>* &pR) {
	AVLNode<T>* &ptr = pR->_pLeft;
	pR->_pRight;
	ptr->_pRight;
}
template<class T>
void AVLTree<T>::rotLR(AVLNode<T>* &pR) {
	pR->_pRight = rotRight(pR->_pRight);
	return rotLeft(pR);
}
template<class T>
void AVLTree<T>::rotRL(AVLNode<T>* &pR) {
	pR->_pLeft = rotLeft(pR->_pLeft);
	return rotRight(pR);
}
template<class T>
bool AVLTree<T>::balanceLeft(AVLNode<T>* &pR) {
	pR->_bFactor--;
	if (pR->_bFactor == 0)
		return false;
	if (pR->_bFactor == -1)
		return true;
	if (pR->_bFactor == -2) {
		if (pR->_pLeft->_bFactor == 1)
			rotLeft(pR->_pLeft);
		rotRight(pR);
		return false;
	}
}
template<class T>
bool AVLTree<T>::balanceRight(AVLNode<T>* &pR) {
	pR->_bFactor++;
	if (pR->_bFactor == 0)
		return false;
	if (pR->_bFactor == 1)
		return true;
	if (pR->_bFactor == 2) {
		if (pR->_pLeft->_bFactor == -1)
			rotRight(pR->_pRight);
		rotLeft(pR);
		return false;
	}
}

#endif //A02_DSALIB_H
