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
	
	int last = 0; //defines where in the array the last pointer is

	for(int i = 0; i < 128; i++)
	{
		if(leaves[i]->freq == 0)
			leaves[i] = NULL;
		else
			last = i;
	}

	while(last > 0)
	{
		//get two smallest nodes in array
		struct Node *left = leaves[last];
		struct Node *right = leaves[last-1];

		//create parent node for them with a freq as the sum of the two
		struct Node *par = malloc(sizeof(struct Node));
		
		par->left = left;
		par->right = right;
		par->freq = left->freq + right->freq;
		par->isLeaf = 0;

		leaves[last] = NULL;
		leaves[last-1] = par;

		last -= 1;

		for(int i = last; i--; par->freq > leaves[i-1]->freq && i > 0) //insert new parent node into array so it remains in order
		{
			struct Node *temp = leaves[i-1];
			leaves[i-1] = par;
			leaves[i] = temp;
		}
	}

	return leaves[0];
}


