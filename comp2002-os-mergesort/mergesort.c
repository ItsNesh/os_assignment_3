/**
 * This file implements parallel mergesort.
 */

#include "mergesort.h"

#include <stdio.h>
#include <stdlib.h> /* for malloc */
#include <string.h> /* for memcpy */

/* this function will be called by mergesort() and also by parallel_mergesort().
 */
void merge(int leftstart, int leftend, int rightstart, int rightend) {
  // Initialize indices: left_idx tracks left subarray, right_idx tracks right
  // subarray, temp_idx tracks position in temp array
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
  memcpy(&A[leftstart], &B[leftstart],
         (rightend - leftstart + 1) * sizeof(int));
}

/* this function will be called by parallel_mergesort() as its base case. */
void my_mergesort(int left, int right) {
  if (left >= right) {  // Base case, if the subarray has 1 or no elements then
                        // it's already sorted.
    return;
  }

  int middle = (left + right) /
               2;  // Find the middle index to divide the array into two halves.
  my_mergesort(left, middle);  // Recursively sort the left half. Left is the
                               // same as leftstart, middle is leftend.
  my_mergesort(middle + 1, right);  // Recursively sort the right half. middle +
                                    // 1 is rightstart, right is rightend.
  merge(left, middle, middle + 1, right);  // Merge the two sorted halves.
}

/* this function will be called by the testing program. */
void* parallel_mergesort(void* arg) {
  // 1. Extract arguments
  struct argument* args = arg;
  int left = args->left;
  int right = args->right;
  int level = args->level;

  // 2. If base case (when the max number of levels) is reached, call
  // my_mergesort()
  if (level >= cutoff) {
    my_mergesort(left, right);
    return args;
  }

  // 3. Otherwise, create two new children threads for the next level
  pthread_t leftThread, rightThread;

  struct argument* leftThreadArgs =
      (struct argument*)malloc(sizeof(struct argument));
  struct argument* rightThreadArgs =
      (struct argument*)malloc(sizeof(struct argument));

  int middle = (left + right) / 2;
  // Left thread gets the indexes of the array that are on the left half
  leftThreadArgs->left = left;
  leftThreadArgs->right = middle;
  leftThreadArgs->level = level + 1;
  pthread_create(&leftThread, NULL, parallel_mergesort, (void*)leftThreadArgs);
  // Right thread gets the indexes of the array that are on the right half
  rightThreadArgs->left = middle + 1;
  rightThreadArgs->right = right;
  rightThreadArgs->level = level + 1;
  pthread_create(&rightThread, NULL, parallel_mergesort,
                 (void*)rightThreadArgs);

  // 3. Wait for them to finish
  pthread_join(leftThread, NULL);
  pthread_join(rightThread, NULL);

  // 4. Merge the two sorted halves
  merge(left, middle, middle + 1, right);

  // 5. Free the memory
  free(leftThreadArgs);
  free(rightThreadArgs);
}

/* we build the argument for the parallel_mergesort function. */
struct argument* buildArgs(int left, int right, int level) {
  struct argument* arg = (struct argument*)malloc(
      sizeof(struct argument));  // Allocate memory for the argument struct.

  // Fill in the fields of arg.
  arg->left = left;
  arg->right = right;
  arg->level = level;

  // Return the pointer to the argument struct.
  return arg;
}
