#include <stdio.h>
#include "huffman.h"

int main()
{
	struct Node *counts[128];
        printf("%d", stdin==NULL);
	countLetters(stdin, counts);
	for(char i = 0; i < 128; i++)
	{
		printf("%c: %d\n", counts[i]->val, counts[i]->freq);
	}
	return 1;
}
