#pragma once
#ifndef CMAP
#define CMAP

#include <string>

#define ROOT_IDX 1
#define CHUNK_SIZE (1024) //TODO: test with different sizes 1,2,3,5..2000

// TODO needs to changewhen switching to templates
enum ProcessResult {Deleted=-1,NotFound=-2};

class CMap
{
private:
	// structure holding the key/value pair
	// TODO StaticPair will become generic
	struct StaticPair
	{
		int key;
		std::string value;
		// constructor for easier initialisation
		StaticPair() {};
		StaticPair(int newK, std::string newV) {
			key = newK;
			value = newV;
		};
	};
	// struct holding the fixed-size array
	struct Chunk
	{
		StaticPair** data;
		Chunk* next;
		Chunk() {
			data = new StaticPair*[CHUNK_SIZE];
			// initialise values to nullptr
			for (int i = 0; i < CHUNK_SIZE; i++)
			{
				data[i] = nullptr;
			}
			next = nullptr;
		}
	};
	// inner CRUD functionality
	void _treeInsert(int, int, std::string);
	void _treeUpdate(int, int, std::string);
	std::string _treeGet(int, int);
	// Attributes
	// array of pointers to StaticPair instances
	// TODO: switch to structure
	// StaticPair** _tree;

	// keeps track of the array size
	int _numOfChunks;
	// pointer to first chunk
	Chunk* _root;
public:
	// CRUD functionality
	void Insert(int, std::string);
	void Update(int, std::string);
	void Erease(int);
	std::string Get(int);
	// Operators
	std::string operator[](int);
	// Construcor and destructors
	CMap();
	~CMap();
};

#endif