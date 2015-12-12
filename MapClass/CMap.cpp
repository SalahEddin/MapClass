#include "CMap.h"
#ifndef CMAP_CPP
#define CMAP_CPP

#pragma region API
template <typename K, typename V>
V CMap<K, V>::Get(K key)
{
	return _treeGet(ROOT_IDX, key);
}

template <typename K, typename V>
void CMap<K, V>::Insert(K newK, V newV) {
	// TODO first searches if key already exists, then updates it

	// will call _treeInsert with index ROOT_IDX
	// because tree node in array starts from 1
	this->_treeInsert(ROOT_IDX, newK, newV);
}
template <typename K, typename V>
void CMap<K, V>::Update(K key, V newV)
{
	_treeUpdate(ROOT_IDX, key, newV);
}
template <typename K, typename V>
void CMap<K, V>::Erease(K key)
{
	_treeUpdate(ROOT_IDX, key, "Deleted");
}
#pragma endregion

#pragma region Inner CRUD
template <typename K, typename V>
V CMap<K, V>::_treeGet(int init_index, K key) const
{

	V result = NULL/*"No Result Found"*/;

	bool isFound = false;
	int tree_idx = init_index;
	// loop as long as there are more chunks (and element is not found yet)
	for (chunkStruct* chunkIte = _root; (chunkIte) && (!isFound); chunkIte = chunkIte->next)
	{
		// re-size chunk index
		int chunk_idx = tree_idx%CHUNK_SIZE;
		// search element within chunk
		while (chunk_idx < CHUNK_SIZE)
		{
			// TODO: better usage
			pairStruct* item = chunkIte->data[chunk_idx];
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


template <typename K, typename V>
void CMap<K, V>::_treeUpdate(int init_index, K key, V newV) const
{
	bool isFound = false;
	int tree_idx = init_index;
	// loop as long as there are more chunks (and element is not found yet)
	for (chunkStruct* chunkIte = _root; (chunkIte) && (!isFound); chunkIte = chunkIte->next)
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

template <typename K, typename V>
void CMap<K, V>::_treeInsert(int init_index, K newKey, V newVal) {
	bool isAssigned = false;
	int tree_idx = init_index;
	chunkStruct* previousChunk = nullptr;
	// loop as long as there are more chunks (and element is not found yet)
	for (chunkStruct* chunkIte = _root; (chunkIte) && (!isAssigned); chunkIte = chunkIte->next)
	{
		// re-size chunk index
		int chunk_idx = tree_idx%CHUNK_SIZE;
		// search element within chunk
		while (chunk_idx < CHUNK_SIZE)
		{
			// current init_index is empty
			if (chunkIte->data[chunk_idx] == nullptr)
			{
				chunkIte->data[chunk_idx] = new pairStruct(newKey, newVal);
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
		auto temp = new chunkStruct();
		// connect it to the list
		previousChunk->next = temp;
		// increase the number of chunk counter
		_numOfChunks++;
		// add the element
		temp->data[tree_idx%CHUNK_SIZE] = new pairStruct(newKey, newVal);
	}

}
#pragma endregion

#pragma region Operators
template <typename K, typename V>
V CMap<K, V>::operator[](K key)
{
	// TODO this method will lookup if the key exists, if yes, then returns the value. 
	// If the key does not exist: 1.check if there's space, 2. then create a new key value pair
	return this->_treeGet(ROOT_IDX, key);
	// if not found, then return some error
}
#pragma endregion

#pragma region Construcor and destructors
template <typename K, typename V>
CMap<K, V>::CMap() : _numOfChunks(0)
{
	_root = new chunkStruct();
}

template <typename K, typename V>
CMap<K, V>::~CMap()
{
	// TODO clean memory
	chunkStruct* chnkIte = _root;
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
#pragma endregion
#endif