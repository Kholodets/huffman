
/**
 * Provides bit input and output functionality for huffman encoding project
 * @file bitio.c
 * @author Kholodets
*/

#include <stdio.h>
#include <stdlib.h>

struct BitIO 
{
	FILE *stream;
	int i;
	unsigned char buffer;
	int open;
};

struct BitIO *openBitIn(FILE *stream)
{
	struct BitIO *io = malloc(sizeof(struct BitIO));
	io->stream = stream;
	io->i = 0;
	io->open = 1;
	if(!feof(stream))
	{
		io->buffer = getc(stream);
		return io;
	}
	

	return NULL;
}

//Note: This will dump the rest of the byte currently being read
int closeBitIn(struct BitIO *io)
{
	io->open = 0;
	return 0;
}

struct BitIO *openBitOut(FILE *stream)
{
	struct BitIO *io = malloc(sizeof(struct BitIO));
	io->stream = stream;
	io->i = 0;
	io->open = 1;
	return io;
}

int closeBitOut(struct BitIO *io)
{
	io->buffer = (io->buffer) << (7-(io->i));
	putc(io->buffer, io->stream);
	io->buffer = 0;
	io->i = 0;
	io->open = 0;
	return 0;
}

int readBit(struct BitIO *io)
{
	if(io->open)
	{
		int value = ((io->buffer << (io->i))&128)>>7;
		(io->i)++;
		if((io->i) == 8)
		{
			io->i = 0;
			if(feof(io->stream))	
				closeBitIn(io);
			else
				io->buffer = getc(io->stream);
		}
		return value;
	}

	return 2;
}

int writeBit(int value, struct BitIO *io)
{
	io->buffer += value;
	if((io->i) == 7)
	{
		putc(io->buffer, io->stream);
		io->i = 0;
		io->buffer = 0;
	} else
	{
		io->buffer = (io->buffer) << 1;
		(io->i)++;
	}

	return 0;//outBuffer;
}
