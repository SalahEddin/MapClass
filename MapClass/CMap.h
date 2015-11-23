#pragma once
#ifndef CBINTREE
#define CBINTREE

#include <string>

#define ROOT_IDX 1
#define INIT_MAP_SIZE 25


class CMap
{
private:
	struct StaticPair
	{
		int key;
		std::string value;
		StaticPair() {};
		StaticPair(int newK, std::string newV) {
			key = newK;
			value = newV;
		};
	};
	void _treeInsert(int, int, std::string);
	void _treeUpdate(int, int, std::string);
	std::string _treeGet(int, int);
	StaticPair** _tree;
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