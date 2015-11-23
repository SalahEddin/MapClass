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
	void Get();
	CBinTree(const int);
	~CBinTree();

private:
	void _treeInsert(int, int, std::string);
	StaticPair** _tree;
	int _treeSize;
};

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

void CBinTree::Insert(int newK, std::string newV) {
	// TODO first searches if key already exists, then updates it

	// will call _treeInsert with index ROOT_IDX
	// because tree node in array starts from 1
	this->_treeInsert(ROOT_IDX, newK, newV);
}

void CBinTree::_treeInsert(int index, int newK, std::string newV) {
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
#endif