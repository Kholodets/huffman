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
		par->freq = (left->freq) + (right->freq);
		//printf("%d\n", par->freq);
		par->isLeaf = 0;

		right->parent = par;
		left->parent = par;

		leaves[last] = NULL;
		leaves[last-1] = par;

		last -= 1;

		int i = last-1;

		while(i >= 0 && par->freq > leaves[i]->freq) //insert new parent node into array so it remains in order
		{
			struct Node *temp = leaves[i];
			leaves[i] = par;
			leaves[i+1] = temp;
			i--;
		}

	}

	return leaves[0];
}

//you MUST have opened a bitio out stream before using this
int encodeTree(struct Node *head)
{
	//this will just be recursive because why not
	if(head->isLeaf)
	{
		writeBit(1);

		for(int i = 0; i < 8; i++)
		{
			writeBit(((head->val << i)&128)>>7);
		}

	} else {
		writeBit(0);
		encodeTree(head->left);
		encodeTree(head->right);
	}

	return 1;
}

struct Node *decodeTree()
{
	struct Node *me = malloc(sizeof(struct Node));
	me->isLeaf = readBit();

	if(me->isLeaf)
	{
		char v = 0;
		for(int i = 0; i < 8; i++)
		{
			v = v << 1;
			v += readBit();
		}

		me->val = v;
	} else {
		me->left = decodeTree();
		me->right = decodeTree();
	}

	return me;
}


