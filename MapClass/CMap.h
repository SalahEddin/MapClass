#pragma once
template<typename Key,typename Val>
class CMap
{
public:
	// this method will lookup if the key exists, if yes, then returns the value. 
	// If the key does not exist: 1.check if there's space, 2. then create a new key value pair
	Val operator[](Key);
	// TODO overload assignment operator =

	CMap();
	~CMap();

private:
	struct MyPair
	{
		Key k;
		Val v;
	};
	MyPair* dict[];
	int mMax;
	int mCount;

	void insert(Key newKey, Val newVal);

	bool equals(Key);
	// TODO: is this needed?
	bool isUnique();
	bool isFull();
};