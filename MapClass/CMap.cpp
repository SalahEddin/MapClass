#include "CMap.h"

template<typename Key, typename Val>
Val CMap<Key, Val>::operator[](Key reqKey)
{
	// check if requested key resides in the map
	for (int i = 0; i < dict.size(); i++)
	{
		if (dict[i].equals(reqKey))
		{
			return dict[i].v;
		}
	}
	return null;
}

template<typename Key, typename Val>
CMap<Key, Val>::CMap()
{
	mMax = 10;
	mCount = 0;
	dict = new MyPair[mMax];
}

template<typename Key, typename Val>
void CMap<Key, Val>::insert(Key newKey, Val newVal)
{
	if (mCount < mMax)
	{
		dict[mCount] = new MyPair(newKey, newVal);
		mCount++;
	}
	else
	{
		// TODO: throw an exception
	}
}

template<typename Key, typename Val>
void CMap<Key, Val>::erease(Key k)
{
}

template<typename Key, typename Val>
bool CMap<Key, Val>::equals(Key item)
{
	return (this.k < item && item < this.k) ? true : false;
}

template<typename Key, typename Val>
bool CMap<Key, Val>::isUnique()
{
	return false;
}

template<typename Key, typename Val>
bool CMap<Key, Val>::isFull()
{
	return false;
}
