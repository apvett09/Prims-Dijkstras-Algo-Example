//Program Name: minHeapPQ.cpp
//Programmer Name: Anthony Vettraino
//Description: minHeapPQ class implementation file
//Date Created: 8/3/2021

#include "minHeapPQ.h"

using namespace std;


//Description: Finds the parent
//Pre-condition: minHeapPQ must contain elements
//Post-condition: returns the parent index
int minHeapPQ::parent(int i)
{
	return (i - 1) / 2;
}

//Description: Finds the left child
//Pre-condition: minHeapPQ must contain elements
//Post-condition: returns the left child
int minHeapPQ::left(int i)
{
	return 2 * i + 1;
}

//Description: Finds the right child
//Pre-condition: minHeapPQ must contain elements
//Post-condition: returns the right child
int minHeapPQ::right(int i)
{
	return 2 * i + 2;
}

//Description: constructor
//Pre-condition: minHeapPQ object is created
//Post-condition: assigns 0 to size, capacity is assigned to capacity, resize the heap to capacity
minHeapPQ::minHeapPQ(int capacity)
{
	size = 0;
	this->capacity = capacity;
	heap.resize(capacity);
}

//Description: Insert a key into the min-heap
//Pre-condition: minHeapPQ object is created
//Post-condition: displays message if heap is full,
//                moves element up in correct position
void minHeapPQ::insert(pqData inNode)
{
	if (size == capacity) {
		cout << "Cannot insert - Heap Full" << endl;
		return;
	}

	size++;

	int i = size - 1;
	heap[i] = inNode;

	while (i != 0 && heap[parent(i)].keyWeight > heap[i].keyWeight)
	{
		swap(heap[i], heap[parent(i)]);
		i = parent(i);
	}
}
//Program Name: minHeapPQ.cpp
//Programmer Name: Anthony Vettraino
//Description: minHeapPQ class implementation file
//Date Created: 8/3/2021

#include "minHeapPQ.h"

using namespace std;


//Description: Finds the parent
//Pre-condition: minHeapPQ must contain elements
//Post-condition: returns the parent index
int minHeapPQ::parent(int i)
{
	return (i - 1) / 2;
}

//Description: Finds the left child
//Pre-condition: minHeapPQ must contain elements
//Post-condition: returns the left child
int minHeapPQ::left(int i)
{
	return 2 * i + 1;
}

//Description: Finds the right child
//Pre-condition: minHeapPQ must contain elements
//Post-condition: returns the right child
int minHeapPQ::right(int i)
{
	return 2 * i + 2;
}

//Description: constructor
//Pre-condition: minHeapPQ object is created
//Post-condition: assigns 0 to size, capacity is assigned to capacity, resize the heap to capacity
minHeapPQ::minHeapPQ(int capacity)
{
	size = 0;
	this->capacity = capacity;
	heap.resize(capacity);
}

//Description: Insert a key into the min-heap
//Pre-condition: minHeapPQ object is created
//Post-condition: displays message if heap is full,
//                moves element up in correct position
void minHeapPQ::insert(pqData inNode)
{
	if (size == capacity) {
		cout << "Cannot insert - Heap Full" << endl;
		return;
	}

	size++;

	int i = size - 1;
	heap[i] = inNode;

	while (i != 0 && heap[parent(i)].keyWeight > heap[i].keyWeight)
	{
		swap(heap[i], heap[parent(i)]);
		i = parent(i);
	}
}

//Description: Function to maintain heap structure
//Pre-condition: minHeapPQ object is created and contains elements
//Post-condition: maintains heap structure
void minHeapPQ::heapify(int i)
{
	int leftChild = left(i);
	int rightChild = right(i);
	int smallest = i;

	if ((leftChild < size) && (heap[leftChild].keyWeight < heap[smallest].keyWeight))
	{
		smallest = leftChild;
	}

	if ((rightChild < size) && (heap[rightChild].keyWeight < heap[smallest].keyWeight))
	{
		smallest = rightChild;
	}

	if (smallest != i)
	{
		swap(heap[i], heap[smallest]);
		heapify(smallest);
	}
}

//Description: Removes the smallest element
//Pre-condition: minHeapPQ object is created and contains elements
//Post-condition: returns root which is smallest element and fixes the order
pqData minHeapPQ::extractMin()
{
	//Check if the heap is empty
	if (size == 0)
	{
		cout << "Empty Heap" << endl;
		//return;
	}
	else if (size == 1)
	{
		size--;
		return heap[0];
	}
	else
	{
		//store root node
		pqData root = heap[0];

		//maintain heap shape and order
		heap[0] = heap[size - 1];
		size--;
		heapify(0);

		return root;
	}
}

//Description: Check if heap is empty
//Pre-condition: minHeapPQ object is created
//Post-condition: returns true if empty or false otherwise
bool minHeapPQ::empty()
{
	if (size == 0)
		return true;
	else
		return false;
}