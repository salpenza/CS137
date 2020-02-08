/*
 * main.c
 *
 *  Created on: Feb 20, 2018
 *      Author: sjpenza
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);

	int A = 0, C = 0, G = 0, T = 0;

	char input[BUFSIZ];
	char output[BUFSIZ];
	char pChar;

	FILE *iOpen = NULL;
	FILE *oOpen = NULL;

	printf("Enter a filename to input:\n");
	fgets(input, BUFSIZ, stdin);

	printf("Enter a filename to output:\n");
	fgets(output, BUFSIZ, stdin);

	int iLength = strlen(input);
	int oLength = strlen(output);

	input[iLength - 1] = '\0';
	output[oLength - 1] = '\0';

	iOpen = fopen(input, "r");
	oOpen = fopen(output, "w");

	if (iOpen == NULL) {
		printf("Files cannot be opened.\n");
	} else {
		while (!feof(iOpen)) {

			A = 0;
			T = 0;
			G = 0;
			C = 0;

			while (fscanf(iOpen, "%c", &pChar) != EOF && pChar != '\n') {
				switch (pChar) {
				case 'A':
					A++;
					break;
				case 'T':
					T++;
					break;
				case 'G':
					G++;
					break;
				case 'C':
					C++;
					break;
				}
			}
			fprintf(oOpen, "%d %d %d %d\n", A, C, G, T);
		}

	}

	fclose(iOpen);
	fclose(oOpen);

	printf("Complete\n");
	return EXIT_SUCCESS;
}

