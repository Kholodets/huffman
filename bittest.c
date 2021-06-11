#include <stdio.h>
#include "bitio.h"

void main()
{
	openBitIn(stdin);
	int val;
	do
	{
		val = readBit();
		printf("%d", val);
	} while(val != 2);
	printf("\n");
	openBitOut(stdout);
	int bits[22] = {0,1,1,0,0,0,0,1, 0,1,1,1,0,0,1,1, 0,0,1,1,0,1};
	for(int i = 0; i < 22; i++)
	{
		writeBit(bits[i]);
	}

	closeBitOut();
	printf("\n");
}
