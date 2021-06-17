#include <stdio.h>
#include "huffman.h"
#include "bitio.h"

void printTree(struct Node *head, int level)
{
        for(int i = 0; i < level; i++)
                printf("\t");
        if(head->isLeaf)
                printf("leaf, val = %d\n", head->val);
        else
        {
        	printf("branch: left:\n");
                printTree(head->left, level+1);
                for(int i = 0; i < level; i++)
                	printf("\t");
        	printf("right:\n");
                printTree(head->right, level+1);
        }
}

int main()
{
	struct Node *counts[128];
	countLetters(stdin, counts);
	/*printf("got counts\n");
	for(char i = 0; i < 128; i++)
	{
		if(counts[i]->freq > 0 && counts[i]->val > 31)
		printf("%c: %d\n", counts[i]->val, counts[i]->freq);
	}
	*/
	struct Node *tree = generateTree(counts);
	//printTree(tree, 0);
	/*printf("tree generated, total freq = %d\n", tree->freq);
	printf("left child freq = %d\n", tree->left->freq);
	printf("right child freq = %d\n", tree->right->freq);*/
	openBitOut(stdout);
	encodeTree(tree);
	closeBitOut();
	return 1;
}
