/*
 * Provides the main data structures and functionality for huffman encoding and decoding
 * @file huffman.c
 * @author Kholodets
*/

#include <stdlib.h>
#include <stdio.h>
#include "bitio.h"

struct Node
{
	int freq;
	int isLeaf;
	char val;

	struct Node *parent;
	struct Node *left;
	struct Node *right;
};

//counts letters in given stream and returns an array of pointers to corresponding nodes with each frequency
int countLetters(FILE *stream, struct Node **letters)
{
	for(char i = 0; i < 128; i++)
	{
		letters[i] = malloc(sizeof(struct Node));
		letters[i]->freq = 0;
		letters[i]->isLeaf = 1;
		letters[i]->val = i;
	}

	int eof = 0;
	int letter;
	while((letter = getc(stream))!= EOF)	
		letters[letter]->freq++;

	return 1;
}


int compareNodes(const void *a, const void *b)
{
	return ((*(struct Node**)b)->freq)-((*(struct Node**)a)->freq);
}

struct Node *generateTree(struct Node **freqs)
{
	struct Node *leaves[128];

	//copy frequencies into leaves
	for(int i = 0; i<128; i++)
		leaves[i] = freqs[i];


	qsort(leaves, 128, sizeof(struct Node*), compareNodes);
	
	return leaves[0];//UNFINISHED
}


