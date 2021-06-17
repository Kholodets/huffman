#include <stdio.h>
#include <stdlib.h>

#include "bitio.h"
#include "huffman.h"

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
	openBitIn(stdin);
	struct Node *tree = decodeTree();
	printf("tree decoded\n");
	printTree(tree, 0);
	return 1;
}
