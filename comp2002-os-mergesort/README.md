README.template

## Project Number/Title 

* Authors: Christian Nesci, Nicholas Bologiannis, Trent Morgan
* Group name: Group 61

## Overview - Nicholas to complete
This program implements a parallel merge sort algorithm using the pthread library to sort a randomly-generated array of user specificed size, with a random user specified seed to ensure reproducible test results. It first divides the array into smaller subarrays and creates multiple threads (up to a user specified cutoff level) to sort them concurrently, then merges them back together once sorted. Using a multi-threaded approach allows the program to use multiple CPU cores to achieve at least a 2x performance speedup when compared to single threaded merge sort.


## Manifest - Nicholas to complete

A listing of source files and other non-generated files, and a brief
(one-line) explanation of the purpose of each file.

Makefile: Build configuration file that compiles the source files and links them to create the test-mergesort executable.
mergesort.c: C file that implements the parallel mergesort algorithm.
mergesort.h: Header file that defines data strcutures, function prototypes, and global variables for the parallel mergesort implementation.
test-mergesort.c: C file that tests and benchmarks the parallel mergesort implementation by generating a random array, running the sorting algorithm and then measuring execution time and verifying correctness.

@ItsNesh add any files you make above and give a brief one line explanation.

## Building the project - Trent

This section should tell the user how to build your code.  If you are
delivering a library, where does it need to be installed, or how do you use
it? Is this an executable, if so, how can a user get up to speed as fast as
possible?

## Features and usage - Trent

Summarise the main features of your program. It is also appropriate to
instruct the user how to use your program.

## Testing - Christian

This section should detail how you tested your code. Simply stating "I ran
it a few times and it seems to work" is not sufficient. Your testing needs
to be detailed here.

## Known Bugs

List known bugs that you weren't able to fix (or ran out of time to fix).

## Reflection and Self Assessment - Christian

Discuss the issues you encountered during development and testing. What
problems did you have? What did you have to research and learn on your own?
What kinds of errors did you get? How did you fix them?

What parts of the project did you find challenging? Is there anything that
finally "clicked" for you in the process of working on this project? How well
did the development and testing process go for you?

## Sources Used

If you used any sources outside of the textbook, you should list them here. 
If you looked something up on stackoverflow.com or you use help from AI, and 
fail to cite it in this section, it will be considered plagiarism and dealt 
with accordingly. So be safe CITE!

HackerRank 2016, Algorithms: Merge Sort, Youtube, 28th September, viewed October 28 2025, <https://www.youtube.com/watch?v=KF2j-9iSf4Q&t=372s>
