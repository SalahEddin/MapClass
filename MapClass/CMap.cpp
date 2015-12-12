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
std::string CMap::_treeGet(int init_index, int key) {

	std::string result = "No Result Found";

	bool isFound = false;
	int tree_idx = init_index;
	// loop as long as there are more chunks (and element is not found yet)
	for (Chunk* chunkIte = _root; (chunkIte) && (!isFound); chunkIte = chunkIte->next)
	{
		// re-size chunk index
		int chunk_idx = tree_idx%CHUNK_SIZE;
		// search element within chunk
		while (chunk_idx < CHUNK_SIZE)
		{
			// TODO: better usage
			StaticPair* item = chunkIte->data[chunk_idx];
			// equality !(x < y) && !(y < x)
			if (!(key < item->key) && !(item->key < key))
			{
				result = item->value;
				isFound = true;
				break;
			}
			// key is bigger than indexed pair, try right branch
			if (item->key < key)
			{
				tree_idx = (tree_idx * 2) + 1;
				chunk_idx = tree_idx;
			}
			// key is smaller than indexed pair, try left branch
			else
			{
				tree_idx = tree_idx * 2;
				chunk_idx = tree_idx;
			}
		}
	}

	// TODO handle not found
	return result;
}

void CMap::_treeUpdate(int init_index, int key, std::string newV)
{
	bool isFound = false;
	int tree_idx = init_index;
	// loop as long as there are more chunks (and element is not found yet)
	for (Chunk* chunkIte = _root; (chunkIte) && (!isFound); chunkIte = chunkIte->next)
	{
		// re-size chunk index
		int chunk_idx = tree_idx%CHUNK_SIZE;
		// search element within chunk
		while (chunk_idx < CHUNK_SIZE)
		{
			// equality !(x < y) && !(y < x)
			if (!(key < chunkIte->data[chunk_idx]->key) && !(chunkIte->data[chunk_idx]->key < key))
			{
				chunkIte->data[chunk_idx]->value = newV;
				isFound = true;
				break;
			}
			// key is bigger than indexed pair, try right branch
			if (chunkIte->data[chunk_idx]->key < key)
			{
				tree_idx = (tree_idx * 2) + 1;
				chunk_idx = tree_idx;
			}
			// key is smaller than indexed pair, try left branch
			else
			{
				tree_idx = tree_idx * 2;
				chunk_idx = tree_idx;
			}
		}
	}
	return;
}

void CMap::_treeInsert(int init_index, int newKey, std::string newVal) {
	bool isAssigned = false;
	int tree_idx = init_index;
	Chunk* previousChunk = nullptr;
	// loop as long as there are more chunks (and element is not found yet)
	for (Chunk* chunkIte = _root; (chunkIte) && (!isAssigned); chunkIte = chunkIte->next)
	{
		// re-size chunk index
		int chunk_idx = tree_idx%CHUNK_SIZE;
		// search element within chunk
		while (chunk_idx < CHUNK_SIZE)
		{
			// current init_index is empty
			if (chunkIte->data[chunk_idx] == nullptr)
			{
				chunkIte->data[chunk_idx] = new StaticPair(newKey, newVal);
				isAssigned = true;
				break;
			}
			// key is bigger than indexed pair, try right branch
			if (chunkIte->data[chunk_idx]->key < newKey)
			{
				tree_idx = (tree_idx * 2) + 1;
				chunk_idx = tree_idx;
			}
			// key is smaller than indexed pair, try left branch
			else
			{
				tree_idx = tree_idx * 2;
				chunk_idx = tree_idx;
			}
		}
		// previous points to current chunk, before chunkIte changes
		previousChunk = chunkIte;
	}
	// if no place holds the new pair, then..
	if (!isAssigned)
	{
		// create new chunk
		auto temp = new Chunk();
		// connect it to the list
		previousChunk->next = temp;
		// increase the number of chunk counter
		_numOfChunks++;
		// add the element
		temp->data[tree_idx%CHUNK_SIZE] = new StaticPair(newKey, newVal);
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
CMap::CMap() : _numOfChunks(0)
{
	_root = new Chunk();
}

CMap::~CMap()
{
	// TODO clean memory
	Chunk* chnkIte = _root;
	int index = 1;
	while (chnkIte)
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