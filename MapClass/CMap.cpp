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

	std::string result = "No Result Found";
	while(index < _treeSize)
	{
		if(!(key <_tree[index]->key && _tree[index]->key < key))
		{
			// equality (x < y && y < x)
			result = _tree[index]->value;
			break;
		}
		else if(_tree[index]->key < key)
		{
			// key is bigger than indexed pair, try right branch
			index = (index * 2) + 1;
			continue;
		}
		else
		{
			// key is smaller than indexed pair, try left branch
			index = index * 2;
			continue;
		}

	}
	// TODO handle not found
	return result;
}

void CMap::_treeUpdate(int index, int key, std::string newV)
{
	while (index < _treeSize)
	{
		if (!(key <_tree[index]->key && _tree[index]->key < key))
		{
			// equality (x < y && y < x)
			_tree[index]->value = newV;
			break;
		}
		else if (_tree[index]->key < key)
		{
			// key is bigger than indexed pair, try right branch
			index = (index * 2) + 1;
			continue;
		}
		else
		{
			// key is smaller than indexed pair, try left branch
			index = index * 2;
			continue;
		}

	}
	// TODO handle not found
	return;
}

void CMap::_treeInsert(int index, int newK, std::string newV) {
	while (index < _treeSize)
	{
		if (!_tree[index]) {
			_tree[index] = new StaticPair(newK, newV);
		}
		else if (_tree[index]->key < newK)
		{
			// key is bigger than indexed pair, try right branch
			index = (index * 2) + 1;
			continue;
		}
		else
		{
			// key is smaller than indexed pair, try left branch
			index = index * 2;
			continue;
		}

	}
	// TODO handle not found
	return;
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