
/**
 * Provides bit input and output functionality for huffman encoding project
 * @file bitio.c
 * @author Kholodets
*/

#include <stdio.h>

int inBitIndex;
int outBitIndex;
int inOpen = 0;
int outOpen = 0;
FILE *inStream;
FILE *outStream;
char inBuffer;
char outBuffer;

int openBitIn(FILE *stream)
{
	if(!inOpen)
	{
		inStream = stream;
		inOpen = 1;
		inBitIndex = 0;
		if(!feof(inStream))
		{
			inBuffer = getc(inStream);
			return 1;
		}
	}

	return 0;
}

//Note: This will dump the rest of the byte currently being read
int closeBitIn()
{
	if(inOpen)
	{
		inStream = NULL;
		inOpen = 0;
		inBitIndex = NULL;
		return 1;
	}

	return 0;
}

int openBitOut(FILE *stream)
{
	if(!outOpen)
	{
		outStream = stream;
		outOpen = 1;
		outBitIndex = 0;
		outBuffer = 0;
		return 1;
	}

	return 0;
}

int closeBitOut()
{
	if(outOpen)
	{
		outBuffer = outBuffer << 7-outBitIndex;
		putc(outBuffer, outStream);
		outStream = NULL;
		outBuffer = 0;
		outBitIndex = NULL;
		outOpen = 0;
		return 1;
	}

	return 0;
}

int readBit()
{
	if(inOpen)
	{
		int value = ((inBuffer << inBitIndex)&128)>>7;
		inBitIndex++;
		if(inBitIndex == 8)
		{
			inBitIndex = 0;
			if(feof(inStream))
				closeBitIn(); //premptively closes when reached end of stream so will return 2 on next call
			else
				inBuffer = getc(inStream);
		}
		return value;
	}

	return 2;
}

int writeBit(int value)
{
	outBuffer += value;
	if(outBitIndex == 7)
	{
		putc(outBuffer, outStream);
		outBitIndex = 0;
		outBuffer = 0;
	} else
	{
		outBuffer = outBuffer << 1;
		outBitIndex++;
	}

	return 1;//outBuffer;
}
