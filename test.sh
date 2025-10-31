#!/bin/bash

echo "================================================="
echo " PARALLEL MERGESORT TEST"
echo "================================================="
echo ""

# Performance
echo "================================================="
echo "1. PERFORMANCE TEST (n=100,000,000, seed=1234)"
echo "================================================="
echo ""

for cutoff in 0 1 2 3 4 5 6 7 8; do
	echo "Testing cutoff level $cutoff"
	./test-mergesort 100000000 $cutoff 1234
	echo ""
done

# Random seed
echo "================================================="
echo "2. RANDOM SEED (n=10,000,000, cutoff=4)"
echo "================================================="
echo ""

for seed in 1234 5678 1111 9999 7165 6323 9583 2469; do
	echo "Testing with seed $seed"
	./test-mergesort 10000000 4 $seed
	echo ""
done

# Scalability
echo "================================================="
echo "3. SCALABILITY"
echo "================================================="
echo ""

for size in 1000 100000 1000000 10000000 100000000; do
	echo "Testing array size $size"
	echo "Sequential (cutoff 0):"
	./test-mergesort $size 0 1234
	echo "Parallel (cutoff 4):"
	./test-mergesort $size 4 1234
	echo ""
done

echo "================================================="
echo " ALL TESTS COMPLETE"
echo "================================================="
