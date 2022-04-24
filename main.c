#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/bitio.h"
#include "lib/huffman.h"

int main(int argc, char *argv[])
{
	if(argc < 2) {
		fprintf(stderr, "You didn't provide any arguments!\n");
		return 1;
	}

	int inf = 0;
	int outf = 0;
	char flags[8];
	int flagc = 0;
	int ed = -1; //0 = encode, 1 = decode
	int outp = 0;
	char *in;
	char *out;
	
	for(int i = 1; i < argc; i++) {
		
		if(*argv[i] == '-') {
			for(int j = 1; j < strlen(argv[i]); j++) {

				flags[flagc] = argv[i][j];
				flagc++;

				if(argv[i][j] == 'e')
					ed = 0;
				if(argv[i][j] == 'd')
					ed = 1;
				if(argv[i][j] == 'o')
					outp = 1;
			}
		} else {
			if(!outp) {
				inf = 1;
				in = argv[i];
			} else {
				outf = 1;
				out = argv[i];
			}
		}
	}

	if(ed == -1) {
		fprintf(stderr, "No action specified, use -e or -d to specify encode or decode\n");
		return 1;
	}

	if(ed == 0 && !inf) {
		fprintf(stderr, "Can not encode from stdin, please provide an input file.\n");
		return 1;
	}

	FILE *input = inf ? fopen(in, "r") : stdin;
	FILE *output = outf ? fopen(out, "w+") : stdout;

	if(ed == 0) {
		fprintf(stderr, "Encoding file...");

		struct Node *counts[256];

		countLetters(input, counts);

		struct Node *tree = generateTree(counts);

		struct BitIO *bitsOut = openBitOut(output);

		encodeTree(tree, bitsOut);

		rewind(input);

		encodeText(input, counts, bitsOut);

		closeBitOut(bitsOut);

		freeFreqs(counts);
		freeTree(tree);
		free(bitsOut);

		fclose(input);
		fclose(output);

		fprintf(stderr, "done!\n");

	}

	if(ed == 1) {
		fprintf(stderr, "Decoding file...");

		struct BitIO *bitsIn= openBitIn(input);
		struct Node *tree = decodeTree(bitsIn);


		decodeText(output, tree, bitsIn);

		closeBitIn(bitsIn);
		freeTree(tree);
		free(bitsIn);
		fclose(input);
		fclose(output);

		fprintf(stderr, "done\n");
	}

	return 0;
}
