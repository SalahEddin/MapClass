#pragma once
#ifndef CMAP_H
#define CMAP_H

#define ROOT_IDX 1
#define CHUNK_SIZE (5)

// TODO needs to changewhen switching to templates
enum ProcessResult {Deleted=-1,NotFound=-2};

template<typename K, typename V> class CMap
{
private:
	// structure holding the key/value pair
	struct pairStruct
	{
		K key;
		V value;
		// constructors for easier initialisation
		pairStruct() {};
		pairStruct(K newK, V newV) {
			key = newK;
			value = newV;
		};
	};
	// struct holding the fixed-size array
	struct chunkStruct
	{
		pairStruct** data;
		chunkStruct* next;
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
	// inner CRUD functionality
	V _treeGet(int init_index, K key) const;
	void _treeUpdate(int init_index, K key, V newV) const;
	void _treeInsert(int init_index, K newKey, V newVal);
	// Attributes

	// keeps track of the array size
	int _numOfChunks;
	// pointer to first chunk
	chunkStruct* _root;
public:
	// CRUD functionality
	V Get(K key);
	void Insert(K newK, V newV);
	void Update(K key, V newV);
	void Erease(K key);
	// Operators
	V operator[](K);
	// Construcor and destructors
	CMap();
	~CMap();
};
#endif

#include "CMap.cpp"
