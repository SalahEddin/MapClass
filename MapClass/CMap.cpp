#include "CMap.h"

std::string CMap::Get(int key)
{
	return _treeGet(ROOT_IDX, key);
}

void CMap::Insert(int newK, std::string newV) {
	// TODO first searches if key already exists, then updates it

	// will call _treeInsert with index ROOT_IDX
	// because tree node in array starts from 1
	this->_treeInsert(ROOT_IDX, newK, newV);
}

void CMap::Update(int key, std::string newV)
{
	_treeUpdate(ROOT_IDX, key, newV);
}

void CMap::Erease(int key)
{
	_treeUpdate(ROOT_IDX, key, "Deleted");
}
//////////////////
// Inner CRUD
///////////////
std::string CMap::_treeGet(int index, int key) {
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

void CMap::_treeUpdate(int index, int key, std::string newV)
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

void CMap::_treeInsert(int index, int newK, std::string newV) {
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
//////////////////
// Operators
///////////////
std::string CMap::operator[](int key)
{
	// this method will lookup if the key exists, if yes, then returns the value. 
	// If the key does not exist: 1.check if there's space, 2. then create a new key value pair
	return this->_treeGet(ROOT_IDX, key);
	// if not found, then return some error
}

////////////////
// Construcor and destructors
///////////////
CMap::CMap(const int initSize = INIT_MAP_SIZE)
{
	// TODO size will be Dynamic
	_tree = new StaticPair*[initSize];
	// keep track of size
	_treeSize = initSize;
	// initialise values to nullptr
	for (int i = 0; i < initSize; i++)
	{
		_tree[i] = nullptr;
	}
}

CMap::~CMap()
{
	// TODO clean memory
}