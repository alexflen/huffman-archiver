# Homework #2

## Task

Write a program `hw-02_huffman` that performs compression and decompression using a two-pass Huffman algorithm.
Also implement tests of the written algorithm.

## Requirements for the correctness of the solution

### Basic requirements
Standard and additional requirements apply in this assignment:

* The program is obliged to check the correctness of the arguments (see
[console application](#console-application)).
* It is enough to check relatively trivial errors: going beyond the boundaries of the image and lack of
arguments.
* If one of the arguments turns out to be a non-number instead of a number, the behavior of the program is undefined
(that is, you do not need to process it).
* If there are problems with arguments, file opening, memory allocation, etc., the program must
shut down the job correctly and return a non-zero return code.

### Input and output restrictions

Although the program should not rely on this, when checking the input files are limited to 5MiB. Many
describe the Huffman algorithm for text compression, but the input file can contain any bytes. Y
the program has a time limit of 5 seconds, but in fact it should work noticeably
faster.

### Implementation Requirements

* The implementation should be done in an object-oriented style (for example, include classes
`HuffmanTreeNode', `HuffmanTree', `HuffmanArchiver', but these names are just an example).
* For storing elements, where appropriate, the STL library should be used (for example,
`std::vector`, not a dynamic array).
* I/O must be performed using STL (`iostream`) classes.
* Exceptions should be used.
* A class for automatic testing must be implemented or one of
the libraries (`google test`, `doctest`, ...) must be used.
* Autotests must be written for methods.


*Hints*:
* We recommend making sure that the compressed and then decompressed file is absolutely equivalent
to the original one, do not check by eye (`diff` and analogues).
* We recommend testing on large files, files of different types (text, binary) and on
an empty file.
* We recommend testing your program on synthetic tests that are obviously poorly encoded by the algorithm
Huffman.
* We recommend checking your program for memory leaks.

### Console application

The program starts with flags:
``
./hw-02_huffman [flags]
``
where flags are:
* `-c`: compression,
* `-u': decompression,
* `-f <path>`, `--file <path>`: input file name,
* `-o <path>`, `--output <path>`: name of the resulting file.
The flags can be specified in any order.

The program should display compression/decompression statistics: the size of the source data, the size
of the received data and the size that was used to store auxiliary data in the output
file (for example, tables). No additional text should be output, only dimensions.
All sizes are in bytes.

For example:
``
$ ./huffman -c -f myfile.txt -o result.bin
15678
6172
482
```

The size of the source file (source data): 15678 bytes, the size of the compressed data (without additional
information): 6172 bytes, the size of additional data: 482 bytes. Total compressed file size: 6172+
482 = 6654 bytes.

```
$ ./huffman -u -f result.bin -o myfile_new.txt
6172
15678
482
```

The size of the decompressed file (received data): 15678 bytes, the size of the compressed data (without
additional information): 6172 bytes, additional data size: 482 bytes. The size of the entire
source compressed file: 6172 + 482 = 6654 bytes.

### Separation of responsibilities
* Work with arguments and the entry point to implement in `main.c'.
* Put the algorithm implementation classes in `src/` and `include/`.
* Put the test files in `test/`. The entry point should be `test.cpp `.

## Delivery dates
The task was issued on 11.04.2022.
The task is given ** exactly three ** attempts to pass. Check the terms of attempts with the teacher.

Note that, unlike in the laboratory:

* This homework is more in complexity and volume of code. Please do not delay even until
the interim deadline for delivery.
* You can make ** no more than three** full attempts for the entire time of delivery. At your discretion
intermediate attempts may be added to the teacher, which will be partially checked.
* Due to the volume of the code, solutions can be checked with a significant delay, especially if there is
stylistic remarks.

## Evaluation system
* The task is estimated at 30 points: 15 for correctness, 5 for tests, 10 for style.
