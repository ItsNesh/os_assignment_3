/**
 * This file implements parallel mergesort.
 */

#include <stdio.h>
#include <string.h> /* for memcpy */
#include <stdlib.h> /* for malloc */
#include "mergesort.h"

/* this function will be called by mergesort() and also by parallel_mergesort(). */
void merge(int leftstart, int leftend, int rightstart, int rightend){
	// Initialize indices: left_idx tracks left subarray, right_idx tracks right subarray, temp_idx tracks position in temp array
	int left_idx = leftstart;
	int right_idx = rightstart;
	int temp_idx = leftstart;

	// Merge the two sorted halves into the temp array
	while (left_idx <= leftend && right_idx <= rightend) {
		if (A[left_idx] <= A[right_idx]) {
			B[temp_idx++] = A[left_idx++];
		} else {
			B[temp_idx++] = A[right_idx++];
		}
	}

	// Copy remaining elements from the left half
	while (left_idx <= leftend) {
		B[temp_idx++] = A[left_idx++];
	}

	// Copy remaining elements from the right half
	while (right_idx <= rightend) {
		B[temp_idx++] = A[right_idx++];
	}

	// Copy merged result back into the original array (no cast)
	memcpy(&A[leftstart], &B[leftstart], (rightend - leftstart + 1) * sizeof(int));

	// or with cast:
	// size_t length = (size_t)(rightend - leftstart + 1);
	// memcpy(&A[leftstart], &B[leftstart], length * sizeof(int));
}

/* this function will be called by parallel_mergesort() as its base case. */
void my_mergesort(int left, int right){
}

/* this function will be called by the testing program. */
void * parallel_mergesort(void *arg){
		return NULL;
}

/* we build the argument for the parallel_mergesort function. */
struct argument * buildArgs(int left, int right, int level){
		return NULL;
}

