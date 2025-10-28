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
  //   int i = leftstart;
  //   while (leftstart <= leftend && rightstart <= rightend) {
  //     if (A[leftstart] <= A[rightstart]) {
  //       B[i] = A[leftstart];
  //       leftstart++;
  //     } else {
  //       B[i] = A[leftstart];
  //       rightstart++;
  //     }
  //     i++;
  //   }
}

/* this function will be called by parallel_mergesort() as its base case. */
void my_mergesort(int left, int right) {
  //   if (left < right) {
  //     int mid = left + (right - left) / 2;
  //     my_mergesort(left, mid);
  //     my_mergesort(mid + 1, right);

  //     merge(left, mid, mid + 1, right);
  //   }
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

  // Left thread gets the indexes of the array that are on the left half
  leftThreadArgs->left = 0;
  leftThreadArgs->right = right / 2;
  leftThreadArgs->level = level + 1;
  pthread_create(&leftThread, NULL, parallel_mergesort, (void*)leftThreadArgs);
  // Right thread gets the indexes of the array that are on the right half
  rightThreadArgs->left = (right / 2) + 1;
  rightThreadArgs->right = right;
  leftThreadArgs->level = level + 1;
  pthread_create(&rightThread, NULL, parallel_mergesort,
                 (void*)rightThreadArgs);

  // 3. Wait for them to finish
  pthread_join(leftThread, NULL);
  pthread_join(rightThread, NULL);
}

/* we build the argument for the parallel_mergesort function. */
struct argument* buildArgs(int left, int right, int level) {
  // Allocate memory for arguments struct
  struct argument* args = (struct argument*)malloc(sizeof(struct argument));

  // Initialise data members
  args->left = left;
  args->right = right;
  args->level = level;

  return args;
}
