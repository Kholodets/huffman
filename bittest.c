#include <stdio.h>
#include "bitio.h"

void main()
{
	openBitOut(stdout);
	int bits[17] = {0,1,1,0,0,0,0,1,0,1,1,1,0,0,1,1,0};
	for(int i = 0; i < 16; i++)
	{
		writeBit(bits[i]);
	}
	closeBitOut();
	printf("\n");
}
