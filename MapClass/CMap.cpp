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
	Chunk* chnkIte = _root;
	// loop as long as there are more chunks
	while (chnkIte)
	{
		// search element within chunk
		while (index < CHUNK_SIZE)
		{
			if (!(key < chnkIte->data[index]->key && chnkIte->data[index]->key < key))
			{
				// equality (x < y && y < x)
				result = chnkIte->data[index]->value;
				break;
			}
			else if (chnkIte->data[index]->key < key)
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
		// switch to next chunk
		chnkIte = chnkIte->next;
		index %= CHUNK_SIZE;
	}

	// TODO handle not found
	return result;
}

void CMap::_treeUpdate(int index, int key, std::string newV)
{
	Chunk* chnkIte = _root;
	// loop as long as there are more chunks
	while (chnkIte)
	{
		while (index < CHUNK_SIZE)
		{
			if (!(key <chnkIte->data[index]->key && chnkIte->data[index]->key < key))
			{
				// equality (x < y && y < x)
				chnkIte->data[index]->value = newV;
				break;
			}
			else if (chnkIte->data[index]->key < key)
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
		// switch to next chunk
		chnkIte = chnkIte->next;
		index %= CHUNK_SIZE;
	}
	return;
}

void CMap::_treeInsert(int index, int newK, std::string newV) {

	Chunk* chnkIte = _root;
	// loop as long as there are more chunks
	while (chnkIte)
	{
		while (index < CHUNK_SIZE)
		{
			if (!chnkIte->data[index]) {
				chnkIte->data[index] = new StaticPair(newK, newV);
				return;
			}
			else if (chnkIte->data[index]->key < newK)
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
				// TODO: if index x 2 is bigger than the new array size
			}

		}
		// switch to next chunk
		chnkIte = chnkIte->next;
		index %= CHUNK_SIZE;
	}
	
	// TODO expand to new chunk
	// TODO _root not updating
	// create new chunk
	auto temp = new Chunk();
	chnkIte = temp;
	// insert item
	chnkIte->data[index] = new StaticPair(newK, newV);
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
CMap::CMap()
{
	_root = new Chunk();
}

CMap::~CMap()
{
	// TODO clean memory
	Chunk* chnkIte = _root;
	int index = 1;
	while(chnkIte)
	{
		while (index < CHUNK_SIZE)
		{
			if (chnkIte->data[index])	delete chnkIte->data[index];
			index++;
		}
		// TODO: 0 indices in all chunk are not used BUG
		index = 1;
		// switch to next chunk
		chnkIte = chnkIte->next;
	}
	
}