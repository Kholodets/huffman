struct BitIO
{
	FILE *stream;
	int i;
	unsigned char buffer;
};

struct BitIO *openBitIn(FILE *stream);

int closeBitIn(struct BitIO *io);

struct BitIO *openBitOut(FILE *stream);

int closeBitOut(struct BitIO *io);

int readBit(struct BitIO *io);

int writeBit(int value, struct BitIO *io);
