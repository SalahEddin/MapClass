#include "CMap.h"
#ifndef CMAP_CPP
#define CMAP_CPP

#pragma region API
// TODO return types success/failed
template <typename K, typename V>
V CMap<K, V>::Get(K key)
{
	// V val = _treeGet(ROOT_IDX, key);
	// OutputDebugString(val);
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
V CMap<K, V>::_treeGet(int init_index, K key)
{

	V result = NULL;

	ProcessResult process_result = ProcessResult::EMPTY;
	int tree_idx = init_index;
	int inner_chunk_idx = tree_idx;
	int chunk_number = 0;
	// loop as long as there are more chunks (and element is not found yet)
	for (chunkStruct* chunkIte = _root; (chunkIte) && (process_result == ProcessResult::EMPTY);)
	{
		//////////////////////////////
		// move to next chunk (allocate if needed)
		for (int chunk_steps = 0; chunk_steps < (inner_chunk_idx / CHUNK_SIZE) - chunk_number; chunk_steps++)
		{
			if (!chunkIte->next)
			{
				throw; // the key doesn't exist
			}
			chunkIte = chunkIte->next;
			if (chunk_steps == (inner_chunk_idx / CHUNK_SIZE) - chunk_number - 1)
				chunk_number += chunk_steps + 1;
		}
		// re-size chunk index
		inner_chunk_idx = tree_idx%CHUNK_SIZE;

		//////////////////////////////
		// search element within chunk
		while (inner_chunk_idx < CHUNK_SIZE)
		{
			// current index is holding the same key, update the value
			if (chunkIte->data[inner_chunk_idx] != nullptr)
			{
				if (!(key < chunkIte->data[inner_chunk_idx]->key) && !(chunkIte->data[inner_chunk_idx]->key < key))
				{
					// found the element
					result = chunkIte->data[inner_chunk_idx]->value;
					process_result = ProcessResult::FOUND;
					break;
				}
			}
			// assume key is smaller than indexed pair, try left branch
			tree_idx = tree_idx * 2;
			// if key is bigger than indexed pair, try right branch
			if (chunkIte->data[inner_chunk_idx]->key < key)
				tree_idx += 1;
			inner_chunk_idx = tree_idx;
		}
	}

	// TODO handle not found
	return result;
}

template <typename K, typename V>
ProcessResult CMap<K, V>::_treeUpdate(int init_index, K key, V newV)
{
	ProcessResult process_result = ProcessResult::EMPTY;
	int tree_idx = init_index;
	int inner_chunk_idx = tree_idx;
	int chunk_number = 0;
	// loop as long as there are more chunks (and element is not found yet)
	for (chunkStruct* chunkIte = _root; (chunkIte) && (process_result == ProcessResult::EMPTY);)
	{
		//////////////////////////////
		// move to next chunk (allocate if needed)
		for (int chunk_steps = 0; chunk_steps < (inner_chunk_idx / CHUNK_SIZE) - chunk_number; chunk_steps++)
		{
			if (!chunkIte->next)
			{
				process_result = ProcessResult::NOT_FOUND; // the key doesn't exist
			}
			chunkIte = chunkIte->next;
			if (chunk_steps == (inner_chunk_idx / CHUNK_SIZE) - chunk_number - 1)
				chunk_number += chunk_steps + 1;
		}
		// re-size chunk index
		inner_chunk_idx = tree_idx%CHUNK_SIZE;

		//////////////////////////////
		// search element within chunk
		while (inner_chunk_idx < CHUNK_SIZE)
		{
			// current index is holding the same key, update the value
			if (chunkIte->data[inner_chunk_idx] != nullptr)
			{
				if (!(key < chunkIte->data[inner_chunk_idx]->key) && !(chunkIte->data[inner_chunk_idx]->key < key))
				{
					process_result = ProcessResult::UPDATED;
					chunkIte->data[inner_chunk_idx]->value = newV;
					break;
				}
			}
			// assume key is smaller than indexed pair, try left branch
			tree_idx = tree_idx * 2;
			// if key is bigger than indexed pair, try right branch
			if (chunkIte->data[inner_chunk_idx]->key < key)
				tree_idx += 1;
			inner_chunk_idx = tree_idx;
		}
	}
	return process_result;
}

template <typename K, typename V>
ProcessResult CMap<K, V>::_treeInsert(int init_index, K newKey, V newVal) {
	ProcessResult process_result = ProcessResult::EMPTY;
	int tree_idx = init_index;
	int inner_chunk_idx = tree_idx;
	int chunk_number = 0;
	// loop as long as there are more chunks (and element is not found yet)
	for (chunkStruct* chunkIte = _root; (chunkIte) && (process_result == ProcessResult::EMPTY);)
	{
		//////////////////////////////
		// move to next chunk (allocate if needed)
		for (int chunk_steps = 0; chunk_steps < (inner_chunk_idx / CHUNK_SIZE)- chunk_number; chunk_steps++)
		{
			if (!chunkIte->next)
			{
				//create new chunk, add it to the list
				chunkIte->next = new chunkStruct();
				// increase the number of chunk counter
				_numOfChunks++;
			}
			chunkIte = chunkIte->next;
			if(chunk_steps == (inner_chunk_idx / CHUNK_SIZE) - chunk_number-1)
				chunk_number+= chunk_steps+1;
		}
		// re-size chunk index
		inner_chunk_idx = tree_idx%CHUNK_SIZE;

		//////////////////////////////
		// search element within chunk
		while (inner_chunk_idx < CHUNK_SIZE)
		{
			// current index is holding the same key, update the value
			if (chunkIte->data[inner_chunk_idx] != nullptr)
			{
				if (!(newKey < chunkIte->data[inner_chunk_idx]->key) && !(chunkIte->data[inner_chunk_idx]->key < newKey))
				{
					chunkIte->data[inner_chunk_idx]->value = newVal;
					process_result = ProcessResult::UPDATED;
					break;
				}
			}
			// current index is empty
			if (chunkIte->data[inner_chunk_idx] == nullptr)
			{
				// create new element
				chunkIte->data[inner_chunk_idx] = new pairStruct(newKey, newVal);
				_numOfitems++;
				process_result = ProcessResult::INSERTED;
				break;
			}
			// assume key is smaller than indexed pair, try left branch
			tree_idx = tree_idx * 2;
			// if key is bigger than indexed pair, try right branch
			if (chunkIte->data[inner_chunk_idx]->key < newKey)
				tree_idx += 1;
			inner_chunk_idx = tree_idx;
		}
	}
	return process_result;
}

template <typename K, typename V>
ProcessResult CMap<K, V>::_treeDelete(int init_index, K key)
{
	ProcessResult process_result = ProcessResult::EMPTY;
	int tree_idx = init_index;
	int inner_chunk_idx = tree_idx;
	int chunk_number = 0;
	// loop as long as there are more chunks (and element is not found yet)
	for (chunkStruct* chunkIte = _root; (chunkIte) && (process_result == ProcessResult::EMPTY);)
	{
		//////////////////////////////
		// move to next chunk (allocate if needed)
		for (int chunk_steps = 0; chunk_steps < (inner_chunk_idx / CHUNK_SIZE) - chunk_number; chunk_steps++)
		{
			if (!chunkIte->next)
			{
				throw; // the key doesn't exist
			}
			chunkIte = chunkIte->next;
			if (chunk_steps == (inner_chunk_idx / CHUNK_SIZE) - chunk_number - 1)
				chunk_number += chunk_steps + 1;
		}
		// re-size chunk index
		inner_chunk_idx = tree_idx%CHUNK_SIZE;

		//////////////////////////////
		// search element within chunk
		while (inner_chunk_idx < CHUNK_SIZE)
		{
			// current index is holding the same key, update the value
			if (chunkIte->data[inner_chunk_idx] != nullptr)
			{
				if (!(key < chunkIte->data[inner_chunk_idx]->key) && !(chunkIte->data[inner_chunk_idx]->key < key))
				{
					chunkIte->data[inner_chunk_idx]->isDeleted = true;
					process_result = ProcessResult::DELETED;
					break;
				}
			}
			// assume key is smaller than indexed pair, try left branch
			tree_idx = tree_idx * 2;
			// if key is bigger than indexed pair, try right branch
			if (chunkIte->data[inner_chunk_idx]->key < key)
				tree_idx += 1;
			inner_chunk_idx = tree_idx;
		}
	}
	return process_result;
}
#pragma endregion

#pragma region Operators
template <typename K, typename V>
V CMap<K, V>::operator[](K& key)
{
	// TODO this method will lookup if the key exists, if yes, then returns the value. 
	// If the key does not exist: 1.check if there's space, 2. then create a new key value pair
	return _treeGet(ROOT_IDX, key);
	// if not found, then return some error
}
#pragma endregion

#pragma region Construcor and destructors
template <typename K, typename V>
CMap<K, V>::CMap() : _numOfChunks(1), _numOfitems(0)
{
	_root = new chunkStruct();
}

template <typename K, typename V>
CMap<K, V>::~CMap()
{
	int i = 0;
	for (chunkStruct* chunkIte = _root; chunkIte; chunkIte = chunkIte->next)
	{
		delete[] chunkIte->data;
		i++;
	}
}
#pragma endregion
#endif