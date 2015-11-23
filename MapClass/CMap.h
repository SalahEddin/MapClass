#pragma once
#ifndef CMAP
#define CMAP

#include <string>
// generics will be key and value types
class CMap
{
public:
	// this method will lookup if the key exists, if yes, then returns the value. 
	// If the key does not exist: 1.check if there's space, 2. then create a new key value pair
	std::string operator[](int);
	// TODO overload assignment operator =
	void Insert(int, std::string);
	void Erease(int);
	CMap();
	~CMap();

private:
	struct MyPair
	{
		int k;
		std::string v;
	};
	
	const int mMax;
	MyPair* dict[];

	bool equals(int);
	// TODO: is this needed?
	bool isUnique();
	bool isFull();
};
#endif