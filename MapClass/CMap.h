/*
	for neater view, press Ctrl+M,Ctrl+O (collapses all, region views)
*/
#pragma once

#ifndef CMAP_H
#define CMAP_H

#define ROOT_IDX 1
#define CHUNK_SIZE (4000)

// TODO needs to changewhen switching to templates
enum class ProcessResult { DELETED, NOT_FOUND, UPDATED, INSERTED, EMPTY, FOUND };

template<typename K, typename V> class CMap
{
public:
#pragma region Public methods
	// elements and chunks count getters, mostly used for testing
	int chunksCount() const
	{
		return _numOfChunks;
	}
	int count() const
	{
		return _numOfitems;
	}
	// CRUD functionality
	V Get(K key);
	void Insert(K newK, V newV);
	void Update(K key, V newV);
	void Erease(K key);
	// Operators
	V operator[](K&);
	// Construcor and destructors
	CMap();
	~CMap();
#pragma endregion

#pragma region pair structure
	// structure holding the key/value pair
	struct pairStruct
	{
		K key;
		V value;
		bool isInserted;
		// constructors for easier initialisation
		pairStruct() : isInserted(false), isDeleted(false) {};
		pairStruct(K newK, V newV): isInserted(false), isDeleted(false)
		{
			key = newK;
			value = newV;
		};
		// TODO is '=' public or private
	private:
		bool isDeleted;
	};
#pragma endregion

private:
#pragma region Private methods
	// inner CRUD functionality
	V _treeGet(int init_index, K key);
	ProcessResult _treeUpdate(int init_index, K key, V newV);
	// TODO in case of success returns a pointer to the element inserted and isAdded = true, 
	// if updated isAdded = false with a valid pointer
	// if it wasn't added, then return nullptr with message
	ProcessResult _treeInsert(int init_index, K newKey, V newVal);
	ProcessResult _treeDelete(int init_index, K key);
#pragma endregion

#pragma region Private Attributes
	// struct holding the fixed-size array
	struct chunkStruct
	{
		pairStruct** data;
		chunkStruct* next;
		// constructor
		chunkStruct() {
			data = new pairStruct*[CHUNK_SIZE];
			// initialise values to nullptr
			for (int i = 0; i < CHUNK_SIZE; i++)
			{
				data[i] = nullptr;
			}
			next = nullptr;
		}
	};
	// keeps track of the array size
	int _numOfChunks;
	int _numOfitems;
	// pointer to first chunk
	chunkStruct* _root;
#pragma endregion
};
// TODO Switch to ProcessResult::enum
#endif

#include "CMap.cpp"
