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

int encodeTree(struct Node *head);

struct Node *decodeTree();

int encodeText(FILE *stream, struct Node **freqs);

int decodeText(FILE *stream, struct Node *tree);

int freeFreqs(struct Node **freqs);

int freeTree(struct Node *tree);
