#pragma once
template<typename Key,typename T>
class CMap
{
public:
	T &operator[](key);
	CMap();
	~CMap();

private:
	bool (*comp)(/* TODO: keys or values?*/)
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