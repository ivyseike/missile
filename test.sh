#!/bin/bash

echo "test case 1 result:" >> output
./missile >> output
echo "test case 2 result:" >> output
./missile testcase2/nonexistent.txt testcase2/file2.txt p1 p2 >> output

echo "test case 3 result:" >> output
./missile testcase3/file1.txt testcase3/file2.txt p1 p2 >> output

echo "test case 4 result:" >> output
./missile testcase4/file1.txt testcase4/file2.txt p1 p2 >> output

echo "test case 5 result:" >> output
./missile testcase5/file1.txt testcase5/file2.txt p1 p2 >> output

echo "test case 6 result:" >> output
./missile testcase6/file1.txt testcase6/file2.txt p1 p2 >> output

echo "test case 7 result:" >> output
./missile testcase7/file1.txt testcase7/file2.txt p1 p2 >> output

echo "test case 8 result:" >> output
./missile testcase8/file1.txt testcase8/file2.txt p1 p2 >> output

echo "test case 9 result:" >> output
./missile testcase9/file1.txt testcase9/file2.txt p1 p2 >> output

echo "test case 10 result:" >> output
./missile testcase10/file1.txt testcase10/file2.txt p1 p2 >> output

echo "test case 11 result:" >> output
./missile testcase11/file1.txt testcase11/file2.txt p1 p2 >> output

echo "test case 12 result:" >> output
./missile testcase12/file1.txt testcase12/file2.txt p1 p2 >> output

echo "test case 13 result:" >> output
./missile testcase13/file1.txt testcase13/file2.txt p1 p2 >> output

echo "test case 14 result:" >> output
./missile testcase14/file1.txt testcase14/file2.txt p1 p2 >> output

echo "test case 15 result:" >> output
./missile testcase15/file1.txt testcase15/file2.txt p1 p2 >> output

echo "test case 16 result:" >> output
./missile testcase16/file1.txt testcase16/file2.txt p1 p2 >> output

echo "test case 17 result:" >> output
./missile testcase17/file1.txt testcase17/file2.txt p1 p2 >> output

echo "test case 18 result:" >> output
./missile testcase18/file1.txt testcase18/file2.txt >> output


