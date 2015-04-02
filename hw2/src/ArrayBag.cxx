#include <vector>
#include <cstddef>

// Constructor; creates and initializes an empty Bag of "capacity" size
template <class ItemType>
ArrayBag<ItemType>::ArrayBag(int capacity)
{
	numberOfItems = 0;
	myCapacity = capacity;
	itemArray = new ItemType[capacity];
}

// Copy constructor; creates and initializes Bag from another Bag
template <class ItemType>
ArrayBag<ItemType>::ArrayBag(const ArrayBag& anotherBag)
{
	*this = anotherBag;
}

//destructor
template <class ItemType>
ArrayBag<ItemType>::~ArrayBag()
{
	delete [] itemArray;
}

// Assignment operator
template <class ItemType>
ArrayBag<ItemType>& ArrayBag<ItemType>::operator=(const ArrayBag<ItemType>& anotherBag)
{
	if (this != &anotherBag){
		myCapacity = anotherBag.getCapacity();
		numberOfItems = anotherBag.getCurrentSize();
		delete [] itemArray;
		itemArray = new ItemType[myCapacity];
		for (int i = 0; i < numberOfItems; i++)
		{
			itemArray[i] = anotherBag.itemArray[i];
		}
	}
	return *this;
}

// Return the number of Items being stored in the Bag
template <class ItemType>
int ArrayBag<ItemType>::getCurrentSize() const
{
	return numberOfItems;		
}

// Return the capacity of the bag (the maximum Items it can store) 
template <class ItemType>
int ArrayBag<ItemType>::getCapacity( ) const
{
	return myCapacity;
}

//Resizes the bag's capacity to newCapacity
//if the new size is larger, copy all bag contents
// we don't downsize a bag in HW2
template <class ItemType> 
void ArrayBag<ItemType>::resize(int newCapacity)
{
	myCapacity = newCapacity;
	ItemType* olditems = itemArray;
	itemArray = new ItemType[myCapacity];
	for(int i = 0; i < numberOfItems; i++)
	{
		itemArray[i] = olditems[i];
	}
	delete [] olditems;
}

// Report whether the Bag is empty
// Return true if the Bag is empty (storing no Items);
// Return false if Items exist in the Bag
template <class ItemType>
bool ArrayBag<ItemType>::isEmpty() const
{
	return (numberOfItems == 0);	
}

// Report whether the Bag is full
// Return true if the Bag is filled to capacity
// Return false if there is still room
template <class ItemType>
bool ArrayBag<ItemType>::isFull() const
{
	return (numberOfItems == myCapacity);	
}

// Give the Bag a new Item to store
// If Bag is full, double capacity and add newItem
// Else, Bag must add this Item to its Item array and update its numberOfItems
// If Bag is full after this, return true; else return false
template <class ItemType>
bool ArrayBag<ItemType>::add(const ItemType& newItem)
{
	if(isFull()){
		resize(myCapacity * 2);
		itemArray[numberOfItems] = newItem;
		numberOfItems++;
	}
	else{
		itemArray[numberOfItems] = newItem;
		numberOfItems++;
	}
	
	return (isFull());
}

// Make the Bag act like an empty Bag again
template <class ItemType>
void ArrayBag<ItemType>::clear()
{
	numberOfItems = 0;
}

// Remove an Item from the bag
// If Item is not there, nothing changes and we return false
// Else, we fill in its spot in that Item array and count number of Items down
template <class ItemType>
bool ArrayBag<ItemType>::remove(const ItemType& anItem)
{
	int i = 0;
	while (i < numberOfItems)
	{
		if (itemArray[i] == anItem)
		{
			numberOfItems--;
			itemArray[i] = itemArray[numberOfItems];
			return true;
		}
		else
		{
			i++;
		}
	}
	return false;
}

// Check if an Item is in the Bag
// Return true if it is in the Bag, and false if not
template <class ItemType>
bool ArrayBag<ItemType>::contains(const ItemType& anItem) const
{
	for (int i = 0; i < numberOfItems; i++)
	{
		if (itemArray[i] == anItem)
		{
			return true;
		}
	}
	return false;
}

// Check how many times an Item is in the Bag
// return 0 if it's not there; otherwise,
// return the number of times it occurs
template <class ItemType>
int ArrayBag<ItemType>::getFrequencyOf(const ItemType& anItem) const
{
	int freq = 0;
	for (int i = 0; i < numberOfItems; i++)
	{
		if (itemArray[i] == anItem)
		{
			freq ++;
		}
	}
	return freq;		
}

// Make an output vector of Items from the bag (for checking)
template <class ItemType>
vector<ItemType> ArrayBag<ItemType>::toVector() const
{
	vector<ItemType> bagContents;
	
	for (int i = 0; i < numberOfItems; i++)
	{
		bagContents.push_back(itemArray[i]);
	}
	
	return bagContents;				
}
