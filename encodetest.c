#include <stdio.h>
#include "huffman.h"
#include "bitio.h"

void printTree(struct Node *head, int level)
{
        for(int i = 0; i < level; i++)
                fprintf(stderr, "\t");
        if(head->isLeaf)
                fprintf(stderr, "leaf, val = %d\n", head->val);
        else
        {
        	fprintf(stderr, "branch: left:\n");
                printTree(head->left, level+1);
                for(int i = 0; i < level; i++)
                	fprintf(stderr, "\t");
        	fprintf(stderr, "right:\n");
                printTree(head->right, level+1);
        }
}

int main()
{
	struct Node *counts[256];
	FILE *input = fopen("./in.txt", "r");
	//perror("starting count\n");
	countLetters(input, counts);
	//perror("got counts\n");
	/*for(char i = 0; i < 128; i++)
	{
		if(counts[i]->freq > 0 && counts[i]->val > 31)
		printf("%c: %d\n", counts[i]->val, counts[i]->freq);
	}
	*/
	struct Node *tree = generateTree(counts);
	//printTree(tree, 0);
	//perror("tree generated\n");
	/*printf("left child freq = %d\n", tree->left->freq);
	printf("right child freq = %d\n", tree->right->freq);*/
	openBitOut(stdout);
	encodeTree(tree);
	//perror("encoded tree\n");
	rewind(input);
	//perror("rewound input\n");
	//fprintf(stderr, "%c%c%c%c\n", getc(input), getc(input), getc(input), getc(input));
	encodeText(input, counts);
	closeBitOut();
	freeFreqs(counts);
	freeTree(tree);
	return 1;
}
