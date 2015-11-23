#pragma once
#ifndef CMAP
#define CMAP
template<typename Key,typename Val>
class CMap
{
public:
	// this method will lookup if the key exists, if yes, then returns the value. 
	// If the key does not exist: 1.check if there's space, 2. then create a new key value pair
	Val operator[](Key);
	// TODO overload assignment operator =
	void insert(Key newK, Val newV);
	void erease(Key k);
	CMap();
	~CMap();

private:
	struct MyPair
	{
		Key k;
		Val v;
	};
	
	int mMax;
	int mCount;
	MyPair* dict[];

	bool equals(Key);
	// TODO: is this needed?
	bool isUnique();
	bool isFull();
};
#endif