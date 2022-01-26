struct Node
{
	int freq;
	int isLeaf;
	unsigned char val;

	struct Node *parent;
	struct Node *left;
	struct Node *right;
};

int countLetters(FILE *stream, struct Node **letters);

struct Node* generateTree(struct Node **freqs);

int encodeTree(struct Node *head, struct BitIO *bitsOut);

struct Node *decodeTree(struct BitIO *bitsIn);

int encodeText(FILE *stream, struct Node **freqs, struct BitIO *bitsOut);

int decodeText(FILE *stream, struct Node *tree, struct BitIO *bitsIn);

int freeFreqs(struct Node **freqs);

int freeTree(struct Node *tree);
