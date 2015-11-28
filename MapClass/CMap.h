#pragma once
#ifndef CMAP
#define CMAP

#include <string>

#define ROOT_IDX 1
#define INIT_MAP_SIZE 25

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
	// inner CRUD functionality
	void _treeInsert(int, int, std::string);
	void _treeUpdate(int, int, std::string);
	std::string _treeGet(int, int);
	// Attributes
	// array of pointers to StaticPair instances
	StaticPair** _tree;
	// keeps track of the array size
	int _treeSize;

public:
	// CRUD functionality
	void Insert(int, std::string);
	void Update(int, std::string);
	void Erease(int);
	std::string Get(int);
	// Operators
	std::string operator[](int);
	// Construcor and destructors
	CMap(const int);
	CMap() : CMap(INIT_MAP_SIZE) {};
	~CMap();
};

#endif