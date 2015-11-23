#pragma once
#ifndef CBINTREE
#define CBINTREE

#include <string>

#define ROOT_IDX 1
struct StaticPair
{
	int key;
	std::string value;
	StaticPair() {};
	StaticPair(int newK, std::string newV) {
		key = newK;
		value = newV;
	};
};

class CBinTree
{
public:
	void Insert(int, std::string);
	void Update(int, std::string);
	void Erease(int);
	std::string Get(int);
	
	// Operators

	// this method will lookup if the key exists, if yes, then returns the value. 
	// If the key does not exist: 1.check if there's space, 2. then create a new key value pair
	std::string operator[](int);
	// Construcor and destructors
	CBinTree(const int);
	~CBinTree();

private:
	void _treeInsert(int, int, std::string);
	void _treeUpdate(int, int, std::string);
	std::string _treeGet(int, int);
	StaticPair** _tree;
	int _treeSize;
};

std::string CBinTree::_treeGet(int index, int key) {
	if (index < _treeSize) {
		if (!(key < _tree[index]->key)) {
			if (!(_tree[index]->key < key)) {
				// equality (x < y && y < x)
				return _tree[index]->value;
			}
			else
			{
				// key is bigger than indexed pair, try right branch
				return this->_treeGet((index * 2) + 1, key);
			}
		}
		if (!(_tree[index]->key < key))
		{
			// key is smaller than indexed pair, try left branch
			return this->_treeGet(index * 2, key);
			
		}
	}
	return nullptr;
}
std::string CBinTree::Get(int key)
{
	return _treeGet(ROOT_IDX, key);
}

void CBinTree::Insert(int newK, std::string newV) {
	// TODO first searches if key already exists, then updates it

	// will call _treeInsert with index ROOT_IDX
	// because tree node in array starts from 1
	this->_treeInsert(ROOT_IDX, newK, newV);
}

void CBinTree::Update(int key, std::string newV)
{
	_treeUpdate(ROOT_IDX,key, newV);
}

void CBinTree::Erease(int key)
{
	_treeUpdate(ROOT_IDX, key, "Deleted");
}

void CBinTree::_treeUpdate(int index, int key, std::string newV)
{
	if (index < _treeSize) {
		if (!(key < _tree[index]->key)) {
			if (!(_tree[index]->key < key)) {
				// equality (x < y && y < x), update value
				_tree[index]->value = newV;
				return;
			}
			else
			{
				// key is bigger than indexed pair, try right branch
				this->_treeUpdate((index * 2) + 1, key, newV);
				return;
			}
		}
		if (!(_tree[index]->key < key))
		{
			// key is smaller than indexed pair, try left branch
			this->_treeUpdate(index * 2, key, newV);
			return;

		}
	}
}

void CBinTree::_treeInsert(int index, int newK, std::string newV) {
	if (index < _treeSize) {
		if (!_tree[index]) {
			_tree[index] = new StaticPair(newK, newV);
		}
		else if (newK < _tree[index]->key)
		{
			//key less than node value, add to node[index] left branch
			this->_treeInsert(index * 2, newK, newV);
		}
		else
		{
			//add to node[index] right branch
			this->_treeInsert((index * 2) + 1, newK, newV);
		}
	}
}

inline std::string CBinTree::operator[](int key)
{
	return this->_treeGet(ROOT_IDX, key);
	// if not found, then return some error
}

CBinTree::CBinTree(const int initSize = 25)
{
	_tree = new StaticPair*[initSize];
	// keep track of size
	_treeSize = initSize;
	// initialise values to nullptr
	for (int i = 0; i < initSize; i++)
	{
		_tree[i] = nullptr;
	}
}

CBinTree::~CBinTree()
{
}
#endif