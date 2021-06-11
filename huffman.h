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

int quickSort(struct Node **freqs, int start, int stop);
