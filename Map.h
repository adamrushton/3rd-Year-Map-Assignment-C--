#ifndef _MAP_H
#define _MAP_H

#include <iostream> // Used for outputting to console, both in the header file and in the cpp file
#include <string>

/*

GetMaxSize				 // Return total array size         
GetCurrentSize			 // Return number of occupied slots 
IsEmpty					 // Returns if a map is empty       
Insert - used via AddSet // Adds a new set to the map					  
Remove					 // Removes a set from the map					   
Locate					 // Returns a value for a given key				   
Reset					 // Resets a map, removing all its keys and values 
Swap					 // Swap two values								   
GetIndex				 // Returns the index of the key stored in the map		 
KeyExists				 // Returns true or false depending on if the key exists 
Start					 // Return first iterator TESTED? TEST COMPLETE
End						 // Return last iterator  TESTED? TEST COMPLETE

*/

// Initial storage of key and value It's more of a pair than a map entry
template <typename K, typename V>
struct SSet
{
public:
	K key;   // This will store a key in a set
	V value; // This will store a value in a set
	SSet() 
	{

	}
};

// Creating a new set to be added to the map array
template <typename K, typename V>
SSet<K, V> NewSet(K key, V value)
{	
	SSet<K, V> newSet;
	newSet.key   = key;
	newSet.value = value; 
	return newSet;
}

template <typename K, typename V>
class CIterator
{
	// Friend is used to allow the creation of iterators
	template <typename K, typename V> friend class CMap; // Friend required to access private iterator information
private:
	SSet<K, V>* mSet;

	// Iterators can only be created using the map class via the use of friend
	CIterator(SSet<K, V> &mSet)
	{
		this->mSet = &mSet;
	}

public:
	// Dereferencing operator, used
	const SSet<K, V> operator*() const
	{	// The current set being pointed at
		return *mSet;
	}

	// Pointing to the next map entry, used
	CIterator<K, V> &operator++()
	{
		mSet++;
		return *this;
	}

	// Incrementing operator, used
	CIterator<K, V> operator++(int)
	{
		CIterator<K, V> temp(*this);
		operator++();
		return temp;
	}

	// Check to see if two map entries are the EXACT same. 
	bool operator==(const CIterator<K, V> &different)
	{
		return this->mSet == different.mSet;
	}

	// Check to see if two map entries are different
	bool operator!=(const CIterator<K, V> &different)
	{
		return this->mSet != different.mSet;
	}

	// Declared destructor. Using smart pointers so won't deallocate memory here.
	~CIterator()
	{

	}
};

template <typename K, typename V>
class CMap
{
private:
	const static unsigned int OUT_OF_MEMORY = 1;  // Out of memory error code to return
	const static unsigned int DEFAULT_SIZE  = 50; // Store default size of the array
	const static unsigned int EXPAND_AMOUNT = 2;  // How much bigger the array will be when more space is needed to be added
	const static unsigned int INVALID       = -1; // Invalid error code
	const static unsigned int MULTIPLIER    = 2;  // How much bigger the array will multiply by
	unsigned int mTopIndex = 0;			          // Store the top index of the array
	unsigned int mLimit    = DEFAULT_SIZE;		  // Starting size 
	SSet<K, V>* mMapArray;				          // Map set declaration

public:
	CMap() 
	{
		mMapArray = new SSet<K, V>[mLimit];
	}

	// There will be no errors in inserting because we are doubling the array size
	void Insert(const SSet<K, V> &set)
	{	
		// Changing the value of an EXISTING key if it already EXISTS.
		for (unsigned int i = 0; i < mLimit; i++)
		{
			if (mMapArray[i].key == set.key)
			{
				mMapArray[i].value = set.value;
				return; // Leave the function, the value of the already existing key has been updated
			}
		}

		// When there are no more slots available, we need to create more spaces.
		if (mTopIndex >= mLimit)
		{
			try 
			{
				SSet<K, V>* mTempMapArray = new SSet<K, V>[mLimit * MULTIPLIER]; // Creating a NEW array doubling the original array size.

				// Copy the current array into the new array that has double the size
				for (unsigned int i = 0; i < mLimit; i++)
				{
					mTempMapArray[i] = mMapArray[i];
				}

				delete[] mMapArray;       // Deallocate the memory of the original array 

				mMapArray = mTempMapArray; // Move new array back to the default array 
				mLimit   *= MULTIPLIER;	  // Update new maximum size limit
			}
			catch (typename std::bad_alloc) // Handling the potential chance of running out of memory
			{
				throw OUT_OF_MEMORY;
			}
		}
		mMapArray[mTopIndex] = set; // Add the new map entry
		mTopIndex++;
	}

	void AddSet(K key, V value)
	{
		Insert(NewSet(key, value));
	}
	
	// Removing a set from the map
	void Remove(K key)
	{
		SSet<K, V>* mTempMapArray   = new SSet<K, V>[mLimit]; // Create a temp map array
		unsigned int mCurrentIndex = 0;
		bool mKeyFound			   = false;

		for (unsigned int i = 0; i < mTopIndex; i++, mCurrentIndex++)
		{
			if (mMapArray[i].key != key)
			{
				mTempMapArray[mCurrentIndex] = mMapArray[i];
			}
			else
			{
				mKeyFound = true;
				mCurrentIndex--;
			}

			// Check for end of loop and if key hasnt been found then might aswell just exit out of this function
			if (!mKeyFound && i == mTopIndex - 1 && mMapArray[i].key != key)
			{	// If the key hasn't been found at the last element in the list, just return out of the function
				delete[] mTempMapArray;
				return;
			}
		}
		// Key has been removed so we need to do some adjustments to the map
		mTopIndex = mCurrentIndex;
		delete[] mMapArray;
		mMapArray = mTempMapArray;
	}
	
	// Swap two positions in the set array
	void Swap(K key, K key2)
	{
		int mKey1Index   = INVALID;
		int mKey2Index   = INVALID;
		V mTempKey1Value = INVALID;

		for (unsigned int i = 0; i < mTopIndex; i++)
		{	// Check that both keys exist
			if (mMapArray[i].key == key)
				mKey1Index = i;

			if (mMapArray[i].key == key2)
				mKey2Index = i;

			// Both of the keys exist, so swap them
			if (mKey1Index != INVALID && mKey2Index != INVALID)
			{	// Store key 1 value. Set key 1 value to key 2 value. Set key 2 value to key 1 value
				mTempKey1Value              = mMapArray[mKey1Index].value;
				mMapArray[mKey1Index].value = mMapArray[mKey2Index].value;
				mMapArray[mKey2Index].value = mTempKey1Value;
				return; // Swap successful, exit the function
			}
		}
	}
	
	// Locates the object which has the key supplied.
	// Returns nullptr if it doesn't exist
	V* Locate(K key)
	{
		for (unsigned int i = 0; i < mTopIndex; i++)
		{	// Attempt to locate the value of a key supplied
			if (mMapArray[i].key == key)
			{
				return &mMapArray[i].value;
			}
		}
		return nullptr;
	}
	
	// Check to see if a key exists
	// Returns true if the key exists
	// Returns false if the key could not be found in the map
	bool KeyExists(K key)
	{
		for (unsigned int i = 0; i < mTopIndex; i++)
		{
			if (mMapArray[i].key == key)
			{
				return true;
			}
		}
		return false;
	}

	// Returns the index position of a key that exists in the map
	// If the index can not be found return -1
	int GetIndex(K key)
	{
		for (unsigned int i = 0; i < mTopIndex; i++)
		{
			if (mMapArray[i].key == key)
			{
				return i;
			}
		}
		return INVALID;
	}

	// Get maximum size the map can be
	unsigned int GetMaxSize()
	{
		return mLimit;
	}

	// Get current size of the map
	unsigned int GetCurrentSize()
	{
		return mTopIndex;
	}
	
	// See if the map has no data 
	bool IsEmpty()
	{
		return mTopIndex == 0;
	}

	// Revault back to the hard-coded configuration
	void Reset()
	{
		mLimit    = DEFAULT_SIZE;
		mTopIndex = 0;
		delete[] mMapArray;
		mMapArray = new SSet<K, V>[mLimit];
	}

	// Returns position 0 set in the map array
	CIterator<K, V> Start()
	{
		return CIterator<K, V>(mMapArray[0]);
	}

	// Returns last set in the map array
	CIterator<K, V> End()
	{
		return CIterator<K, V>(mMapArray[mTopIndex]);
	}

	// Deallocate the maps memory
	~CMap()
	{
		delete[] mMapArray;
	}
};

#endif