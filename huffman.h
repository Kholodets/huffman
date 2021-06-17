struct Node
{
	int freq;
	int isLeaf;
	char val;

	struct Node *parent;
	struct Node *left;
	struct Node *right;
};

int countLetters(FILE *stream, struct Node **letters);

struct Node* generateTree(struct Node **freqs);

int encodeTree(struct Node *head);

struct Node *decodeTree();
