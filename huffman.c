/*
 * Provides the main data structures and functionality for huffman encoding and decoding
 * @file huffman.c
 * @author Kholodets
*/

#include <stdlib.h>
#include "bitio.h"

struct Node
{
	int freq;
	int isLeaf;
	char val;

	struct Node* parent;
	struct Node* left;
	struct Node* right;
};


