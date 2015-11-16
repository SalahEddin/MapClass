#pragma once
template<typename Key,typename T>
class CMap
{
public:
	// this method will lookup if the key exists, if yes, then returns the value. 
	// If the key does not exist: 1.check if there's space, 2. then create a new key value pair
	T &operator[](Key);

	CMap();
	~CMap();

private:
	struct MyPair
	{

	};
	MyPair dict[];
	int mMax;
	int mCount;

	void insert(Key newKey, T newVal);

	bool equals(T);
	// TODO: is this needed?
	bool isUnique();
	bool isFull();
};

template<class Key, class T>CMap::CMap()
{
}

template<class Key, class T>CMap::~CMap()
{
}