/**
 * This file implements parallel mergesort.
 */

#include <stdio.h>
#include <string.h> /* for memcpy */
#include <stdlib.h> /* for malloc */
#include "mergesort.h"

/* this function will be called by mergesort() and also by parallel_mergesort(). */
void merge(int leftstart, int leftend, int rightstart, int rightend){
}

/* this function will be called by parallel_mergesort() as its base case. */
void my_mergesort(int left, int right){
	if (left >= right) { // Base case, if the subarray has 1 or no elements then it's already sorted.
		return;
	}
	
	int middle = (left + right) / 2; // Find the middle index to divide the array into two halves. 
	my_mergesort(left, middle); // Recursively sort the left half. Left is the same as leftstart, middle is leftend.
	my_mergesort(middle + 1, right); // Recursively sort the right half. middle + 1 is rightstart, right is rightend.
	merge(left, middle, middle + 1, right); // Merge the two sorted halves.
}

/* this function will be called by the testing program. */
void * parallel_mergesort(void *arg){
		return NULL;
}

/* we build the argument for the parallel_mergesort function. */
struct argument * buildArgs(int left, int right, int level){
	struct argument *arg = malloc(sizeof(struct argument)); // Allocate memory for the argument struct.
	
	// Fill in the fields of arg.
	arg->left = left;
	arg->right = right;
	arg->level = level;
	
	// Return the pointer to the argument struct.
	return arg;
}

