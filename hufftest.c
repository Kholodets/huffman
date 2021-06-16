#include <stdio.h>
#include "huffman.h"
#include "bitio.h"

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
	/*printf("tree generated, total freq = %d\n", tree->freq);
	printf("left child freq = %d\n", tree->left->freq);
	printf("right child freq = %d\n", tree->right->freq);*/
	openBitOut(stdout);
	encodeTree(tree);
	closeBitOut();
	return 1;
}
