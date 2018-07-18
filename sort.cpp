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
void heapsort(int[], int);
void radixsort(int[], int);
void sleepsort(int[], int);
void shellsort(int[], int);
vector<int> randomvalues(int bound, int len);

int main()
{
	/*Quick Sort*/
	vector<int> unsorted = randomvalues(10, 10);
	int length = unsorted.size();
	cout << length << endl;
	quicksort(unsorted, 0, length-1);
	cout << "[";
	for (int i = 0; i < unsorted.size(); i++) {
		cout << unsorted[i];
		if (i != unsorted.size() - 1) {
			cout << ",";
		}
		else {
			cout << "]";
		}
	}
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
	bool made = false;
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
	if (start < end) { //base case is if the 'sorted' index reaches the last element then done
		int i = partition(ar, start, end);
		quicksort(ar, start, i - 1); //left
		quicksort(ar, i+1, end); //right
	}
}

//will place the pivot in a position where all elements left are lower and all elements right are greater
int partition(vector<int>& ar, int start, int end) {
	int numsLower = start-1;
	int *pivot = &ar[end];
	for (int i = start; i <= end; i++) {
		int * ele = &ar[i];
		if (*ele < *pivot) {
			numsLower++;
			swap(ele, &ar[numsLower]);
		}
	}
	swap(pivot, &ar[numsLower + 1]);
	return numsLower + 1;
}

void heapsort(int nums[], int len) {

}

void radixsort(int nums[], int len) {

}

void sleepsort(int nums[], int len) {

}

void shellsort(int nums[], int len) {

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