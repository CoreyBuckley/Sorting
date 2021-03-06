/*

Name: Corey Buckley
Date: 7/1/2018
Purpose: Demonstrate multiple popular sorting algorithms in C++

Summary of Sorts

BUBBLE:

The Bubble Sort has O(n²) average runtime and O(1) space constraints. It takes N-1 passes to sort the collection.

In the main loop logic, you have two pointers. The first one starts at the beginning of the collection
while the second one is one ahead of the first pointer, i and i+1, respectively. This gives us an adjacent pair
of items. For each pair, we compare the value of the first item relative to the second. If we wanted an ascending order, we
would want the first item to be less than the second item. So if the first item is greater, we would swap the position
of the two items then move on to the next pair. By the end of the first pass, the greatest value will have 'bubbled' to the
last spot in the collection. If we continue this process, we'll notice it takes N-1 passes to fully sort the collection. Meaning
if there's 5 items in an array, it will take us 4 passes to fully sort it.

The most amount of swaps will take place when the collection is sorted in the reverse order. The number of swaps will
be n(n+1)/2, or the sum of the set of natural numbers preceeding it. An example situation of this where we sort ascending:

Original array: [40,20,10,3,1]

1ST PASS: (4 swaps)
[20,40,10,3,1] -> [20,10,40,3,1] ->
[20,10,3,40,1] -> [20,10,3,1,40]

2ND PASS: (3 swaps)

[20,10,3,1,40] -> [10,20,3,1,40] ->
[10,3,20,1,40] -> [10,3,1,20,40]

3RD PASS: (2 swaps)

[10,3,1,20,40] -> [3,10,1,20,40] ->
[3,1,10,20,40]

4TH PASS: (1 swap)

[3,1,10,20,40] -> [1,3,10,20,40]

10 swaps total. 4*5/2 = 10

SELECTION:

Selection Sort has an average runtime of O(n²) and a space complexity of O(1). It requires N-1 passes.

The methodology behind Selection Sort is a brute-force approach. You have two pointers, just like in bubble sort. Except this time
the first pointer is held constant while the second pointer iterates through the whole collection. Once again, the second 
pointer is positioned one ahead of the first so we don't waste time evaluating an expression where the two numbers are equal.
If the collection is to be sorted descending, then the logic is that if the value at the second pointer is greater than the value
at the first, swap them*. Once the second pointer reaches the end of the list, the first pointer is incremented. Essentially, we are
brute-forcing what the maximum value should be at each position in the array. 

* Note: Some implementations of Selection Sort swap the two values whenever they are either greater or less than each other. This
		means more swapping. Another approach is using a variable to store the current maximum value then swapping the position
		of the maximum value found with our current position in the array (represented by the first pointer) at the end
		of the inner loop (when the second cursor has reached the end of the collection). 
		Both implementations have been provided: selectionsort and selectionsort_more_swaps, respectively. 

INSERT:


MERGE:


QUICK:


HEAP:


RADIX:


SLEEP:


SHELL:


*/

#include "stdafx.h"
#include <iostream>
#include <random>
#include <vector>
#include <string>
#include <time.h>
#include <iomanip>
#include <cmath>
using namespace std;

void as(int[], int);
void swap(int *, int *);
void bubblesort(int[], int);
void selectionsort(int[], int);
void selectionsort_more_swaps(int[], int);
void insertionsort(vector<int>&);
void shiftRight(vector<int>& ar, int start, int end);
void mergesort(vector<int>&, int, int);
void merge(vector<int>&, int, int);
void quicksort(vector<int>&, int, int);
int partition(vector<int>&, int, int);
int partition_alternate(vector<int>&, int, int);
void heapsort(vector<int>&);
void heapify(vector<int>&, int, int);
void heapify_alternate(vector<int>&, int, int);
void radixsort(int[], int);
void sleepsort(int[], int);
void shellsort(int[], int);
void gravitysort2(vector<int>&);
void makeWidth(vector<int>& columnBeads, const int& width);
void printBeads(vector<vector<int>>& beads);
void fall(vector<vector<int>>& beads);
int countBeads(vector<int> columnBeads);
void gravitysort(int*, int);

vector<int> randomvalues(int bound, int len);
void randomvalues(int* ar, int bound, int len);

template<typename SequenceContainer>
void printSC(SequenceContainer);

template<typename SequenceContainer>
void printSC(SequenceContainer, int);

int main()
{
	vector<int> unsorted = randomvalues(1000,100);
	#pragma region Quick_Sort
	//vector<int> unsorted = randomvalues(100, 20);
	//int length = unsorted.size();
	////cout << length << endl;
	//quicksort(unsorted, 0, length-1);
	//cout << "[";
	//for (int i = 0; i < unsorted.size(); i++) {
	//	cout << unsorted[i];
	//	if (i != unsorted.size() - 1) {
	//		cout << ",";
	//	}
	//	else {
	//		cout << "]";
	//	}
	//}
	#pragma endregion
	#pragma region Gravity_Sort
	//	const int len = 10000000;
	//	vector<int> beadsV = randomvalues(100, len);
	//	int * beads = (int*)malloc(sizeof(int)*len);
	//	randomvalues(beads, 100, len);
	////	int len = sizeof(beads) / sizeof(beads[0]);
	//	time_t begin = clock();
	//	gravitysort(beads,len);
	//	double dur = double(clock() - begin) / CLOCKS_PER_SEC;
	//	cout << "GRAVITY SORT 1 TIME, INT[]: " << setprecision(8) << fixed << dur << "s" << endl;
	#pragma endregion
	#pragma region Heap_Sort
	//printSC(unsorted);
	heapsort(unsorted);
	printSC(unsorted);
	#pragma endregion
	int x;
	cin >> x;
    return 0;
}

void bubblesort(int nums[], int len) {
	for (int i = 0; i < len - 1; i++) { //takes N-1 passes to fully sort
		for (int j = 0; j < len - 1; j++) {
			int * current = nums+j;
			int * ahead = nums + j + 1;
			if (*current > *ahead) {
				swap(current, ahead);
			}
		}
	}
}

void selectionsort(int nums[], int len) {
	int * p = &nums[0];
	int * bound = p + len;
	while (p != bound - 1) {
		int * max = p;
		int * it = p + 1;
		for (; it != bound; it++) {
			if (*it > *max) {
				max = it;
			}
		}
		swap(p, max);
		p++;
	}
}

void selectionsort_more_swaps(int nums[], int len) {
	int * p = &nums[0];
	int * bound = p + len;
	while (p != bound - 1) {
		int * it = p + 1;
		for (; it != bound; it++) {
			if (*it > *p) {
				swap(p, it); //'max' is the first (or 0th index) of the list since sorted DESC. 
							   //Don't need to assign a var to it
			}
		}
		p++;
	}
}

void insertionsort(vector<int>& ar)
{
	int i, j, key;
	for (int i = 1; i < ar.size(); i++) {
		key = ar[i];
		j = i - 1;
		while (j > -1 && ar[j] > key) {
			ar[j + 1] = ar[j];
			j--;
		}
		ar[j+1] = key;
	}
}

void shiftRight(vector<int>& ar, int start, int end) { //start inclusive, end exclusive
	int insertAtFront = ar[end];
	for (int i = end-1; i > -1; i--) {
		ar[i + 1] = ar[i];
	}
	ar[start] = insertAtFront;
}

void mergesort(vector<int>& ar, int start, int end) {
	if (start < end) {
		int mid = start + (end-start) / 2; //equivalent to (start+end)/2 but won't overflow
		mergesort(ar, start, mid);
		mergesort(ar, mid + 1, end);
		merge(ar, start, end);
	}
}

void merge(vector<int>& ar, int start, int end) {
	int mid = (start + end) / 2;
	int p1 = start;
	int p2 = mid + 1;
	vector<int> newarr;	
	for (int i = start; i <= end; i++) {
		if (p1 > mid) {
			newarr.push_back(ar[p2++]);
		}
		else if (p2 > end) {
			newarr.push_back(ar[p1++]);
		}
		else if (ar[p1] < ar[p2]) {
			newarr.push_back(ar[p1++]);
		}
		else {
			newarr.push_back(ar[p2++]);
		}
	}
	for (int i = 0; i < newarr.size(); i++) {
		ar[start++] = newarr[i];
	}
}

//Need to select a pivot (conventional to select last)
//Want everything to the left of the pivot to be less than it
//Want everything to the right of the pivot be greater than it
//Compare from beginning -> pivot
//Do in-place sort. Example: [8,10,2] pivot = 2. i = 0. 8 > 2 => put on right side of pivot, but 
//																 replace the greater element's position with
//																 10. [10,2,8]
void quicksort(vector<int>& ar, int start, int end) {
	//base case is if the 'sorted' index reaches the last element then done
	if (start < end) {
		int i = partition(ar, start, end);
		quicksort(ar, start, i - 1); //left
		quicksort(ar, i+1, end); //right
	}
}

int partition(vector<int>& ar, int start, int end) {
	int numsLower = start - 1;
	int *pivot = &ar[end];
	for (int i = start; i < end; i++) {
		int * ele = &ar[i];
		if (*ele < *pivot) {
			numsLower++;
			swap(ele, &ar[numsLower]);
		}
	}
	//cout << "[";
	//for (int i = 0; i < ar.size(); i++) {
	//	cout << ar[i];
	//	if (i != ar.size() - 1) {
	//		cout << ",";
	//	}
	//	else {
	//		cout << "]";
	//	}
	//}
	//cout << endl;
	swap(pivot, &ar[numsLower + 1]);
	return numsLower + 1;
}


//Will place the pivot in a position where all elements left are lower and all elements right are greater.
//Alternate partitioning method where you make room next to the pivot and swap an element in.
//Will require two swaps if elements aren't adjacent.
//Based on this video: https://www.youtube.com/watch?v=kUon6854joI&t=89s
int partition_alternate(vector<int>& ar, int start, int end) {
	int compareIndex = start;
	int pivot = end;
	while (compareIndex < pivot) {
		int * ele = &ar[compareIndex];
		if (*ele > ar[pivot]) {
			if (pivot - compareIndex > 1) { //the two elements aren't adjacent, so we need to make room in front
				swap(&ar[pivot], &ar[pivot - 1]);
			}
			swap(&ar[pivot], ele);
			pivot--;
		}
		else {
			compareIndex++;
		}
	}
	return compareIndex;
}

void heapsort(vector<int>& ar)
{
	int len = ar.size();
	for (int i = 0; i < ar.size() - 1; i++) {
		heapify(ar, len-1, len);
		swap(&ar[0], &ar[len - 1]);
		len -= 1;
	}
}

//where i starts at the last index.
//need to keep track of size because
//we subtract 2 from i with each pass
//starts at bottom and goes to root. Only takes 1 swap max per pass.
void heapify(vector<int>& ar, int i, int size)
{
	if (i > 0) {
		int parentIndex = 0;
		int adjacentNodeIndex = i;
		int * max = nullptr;
		bool startingFromLeft = false;
		if (size % 2 == 0) {
			startingFromLeft = true;
		}
		if (startingFromLeft) {
			parentIndex = i / 2;
			//has possibility of being an index error on first go
			adjacentNodeIndex += 1;
		}
		else {
			parentIndex = i / 2 - 1;
			adjacentNodeIndex -= 1;
		}
		if (adjacentNodeIndex < size && ar[adjacentNodeIndex] > ar[i]) {
			max = &ar[adjacentNodeIndex];
		}
		else {
			max = &ar[i];
		}
		if (ar[parentIndex] < *max) {
			swap(&ar[parentIndex], max);
		}
		//subtract 2 because we want to move 
		//to the new set of children
		//each parent has 2 children *potentially*
		heapify(ar, i - 2, size);
	}
}

//starts at root and goes down. May swap with root then parent
void heapify_alternate(vector<int>& ar, int i, int size) //where i is left node index
{
	int leftIndex = 2 * i + 1;
	//so long as i isn't the last level OR it has a child node (which is the size-1%2 part)
	if (leftIndex < size) {
		int * max = nullptr;
		int rightIndex = 2 * i + 2;
		//swap greater child with root if bigger
		max = &ar[leftIndex];
		if (rightIndex < size && ar[rightIndex] > *max) {
			max = &ar[rightIndex];
		}
		if (*max > ar[0]) {
			swap(&ar[0], max);
		}
		//swap with greater child with parent node
		if (i > 0) {
			if (leftIndex < size) {
				if (ar[leftIndex] > ar[i]) {
					max = &ar[leftIndex];
				}
				else if (rightIndex < size && ar[rightIndex] > ar[i]) {
					max = &ar[rightIndex];
				}
				swap(max, &ar[i]);
			}
		}
		heapify(ar, i + 1, size);
	}
}

void radixsort(int nums[], int len) {

}

void sleepsort(int nums[], int len) {

}

void shellsort(int nums[], int len) {

}

//takes about 13s for 10 million elements. Gravitysort2 might take until the heat death to finish that
void gravitysort(int *ar, int len) {
	//Find how many columns we are going to need for each row. 
	int columnLen = ar[0];
	for (int i = 1; i < len; i++) {
		if (ar[i] > columnLen) {
			columnLen = ar[i];
		}
	}
	//Allocate the space needed for a '2d' array of rows by columns
	char * beads = (char*)calloc(columnLen*len, sizeof(char));
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < ar[i]; j++) {
			beads[columnLen*i + j] = 1;
		}
	}
	//Print a display of the beads
	//for (int i = 0; i < len; i++) {
	//	for (int j = 0; j < columnLen; j++) {
	//		cout << (int)beads[i*columnLen + j] << " ";
	//	}
	//	cout << endl;
	//}
	//cout << endl;
	//Outer loop will iterate thru columns
	for (int column = 0; column < columnLen; column++) {
		int sum = 0;
		//Count how many spots are filled in the column
		for (int row = 0; row < len; row++) {
			sum += beads[row*columnLen + column];
			beads[row*columnLen + column] = 0;
		}
		//Reallocate those spots from the bottom up
		for (int i = len - sum; i < len; i++) {
			beads[i*columnLen + column] = 1;
		}
	}
	//Apply changes to original array. Sum of the row (top to bottom) is new array
	for (int i = 0; i < len; i++) {
		int j;
		for (j = 0; j < columnLen && beads[i*columnLen + j]; j++);
		ar[i] = j;
	}
	//Print a display of the beads
	//for (int i = 0; i < len; i++) {
	//	for (int j = 0; j < columnLen; j++) {
	//		cout << (int)beads[i*columnLen + j] << " ";
	//	}
	//	cout << endl;
	//}
	//cout << endl;
}

//far slower than int[] implementation 150ms vs 0ms kinda slow
void gravitysort2(vector<int>& ar) {
	int len = ar.size();
	if (len > 1) {
		vector<vector<int>> beads(len); //Matrix len x (whatever largest value is)
		for (int i = 0; i < len; i++) {
			beads[i] = vector<int>(ar[i], 1);
		}
		fall(beads);
		//printBeads(beads);
		for (int i = 0; i < len; i++) {
			ar[i] = countBeads(beads[i]);
		}
	}
}

void fall(vector<vector<int>>& beads) {
	int len = beads.size();
	int columns = beads[len-2].size(); //will have the column for be dynamic in its limit, 
									   //so we iterate the correct # of columns
	//methodology: iterate thru columns and drop rows
	for (int i = 0; i < columns; i++) { //columns
		for (int j = len-2; j > -1; j--) { //rows
			if (beads[j + 1].size() < beads[j].size()) {
				makeWidth(beads[j + 1], beads[j].size());
				columns = beads[j].size();
			}
			else if (beads[j].size() < beads[j+1].size()) {
				makeWidth(beads[j], beads[j+1].size());
				columns = beads[j+1].size();
			}
			if (beads[j][i] == 1) {
				int rowIter = 1;
				while (j+rowIter < len && beads[j + rowIter][i] == 0) {
					beads[j + rowIter][i] = 1;
					beads[j + rowIter - 1][i] = 0;
					rowIter++;
				}
			}
		}
	}
}

int countBeads(vector<int> columnBeads) {
	int count = 0;
	for (int i = 0; i < columnBeads.size(); i++) {
		if (columnBeads[i] == 1) {
			count++;
		}
	}
	return count;
}

void makeWidth(vector<int>& columnBeads, const int& width) {
	int len = columnBeads.size();
	for (int i = 0; i < width - len; i++) {
		columnBeads.push_back(0);
	}
}

void printBeads(vector<vector<int>>& beads) {
	//verify integrity by output to screen
	for (int i = 0; i < beads.size(); i++) {
		vector<int> columnBeads = beads[i];
		for (int j = 0; j < columnBeads.size(); j++) {
			cout << columnBeads[j] << " ";
		}
		cout << endl;
	}
}

void as(int ar[], int len) {
	int * p;
	p = &ar[0];
	int * bound = p + len;
	int i = 0;
	cout << "[";
	while (p != bound) {
		cout << *p;
		if (p != bound - 1) {
			cout << ",";
		}
		p++;
	}
	cout << "]" << endl;
}

void swap(int * p, int * other) {
	//cout << "The current base value: " << *p << endl;
	//cout << "The greater than value: " << *other << endl << endl;
	int temp = *p;
	*p = *other;
	*other = temp;
}

vector<int> randomvalues(int const bound, int const len) {
	vector<int> values(len);
	srand(time(NULL)); //set random seed
	for (int i = 0; i < len; i++) {
		int ele = rand() % bound + 1;
		values[i] = ele; //1..100   
	}
	return values;
}

void randomvalues(int* ar, int const bound, int const len) {
	srand(time(NULL)); //set random seed
	for (int i = 0; i < len; i++) {
		int ele = rand() % bound + 1;
		ar[i] = ele; //1..100   
	}
}

template<typename SequenceContainer>
void printSC(SequenceContainer ar) {
	cout << "[";
	for (int i = 0; i < ar.size(); i++) {
		cout << ar[i];
		if (i == ar.size() - 1) {
			cout << "]";
		}
		else {
			cout << ",";
		}
	}
	cout << endl;
}

template<typename SequenceContainer>
void printSC(SequenceContainer ar, int len) {
	cout << "[";
	for (int i = 0; i < len; i++) {
		cout << ar[i];
		if (i == len - 1) {
			cout << "]";
		}
		else {
			cout << ",";
		}
	}
}