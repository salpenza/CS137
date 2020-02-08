/*
 * main.c
 *
 *  Created on: Feb 27, 2018
 *      Author: sjpenza
 */
#include <stdio.h>
#include <stdlib.h>
// declaring functions
int computeMaxSequenceLength(int first, int last);
int computeSequenceLength(int p);
int computeNextValue(int s);

int computeMaxSequenceLength(int first, int last) { //finds the max length

	int b = 1, max, i;

	for (i = first; i <= last; i++) {

		if (b) {
			max = computeSequenceLength(i);
		}

		if (max < computeSequenceLength(i)) {
			max = computeSequenceLength(i);
		}
		b = 0;
	}
	return max;
}

int computeSequenceLength(int p) { //finds the sequential length of the number

	int counter = 1; //length

	while (p != 1)
	{
		p = computeNextValue(p);
		counter++;
	}
	return counter;
}

int computeNextValue(int s) { //finds the next value in the sequence

	if (s % 2 == 0) {
		s /= 2;
	} else {
		s = (3 * s) + 1;
	}
	return s;
}

int main(void) {

	setvbuf(stdout, NULL, _IONBF, 0);
	char filename[BUFSIZ];
	char first[BUFSIZ], last[BUFSIZ];

	printf("Enter the output filename: \n");
	atoi(fgets(filename, BUFSIZ, stdin));

	filename[strlen(filename) - 1] = '\0';

	FILE*outputFile = fopen(filename, "w");

	fgets(first, BUFSIZ, stdin);

	while (first[0] != '\n') { //exits loop if line is blank
		fgets(last, BUFSIZ, stdin);
		int firstNum = atoi(first);
		int secondNum = atoi(last);
		if (firstNum <= secondNum) {

			int maxLength = computeMaxSequenceLength(firstNum, secondNum);

			fprintf(outputFile, "%d\t%d\t%d\n", firstNum, secondNum, maxLength); //writes to file
			fgets(first, BUFSIZ, stdin);

		}

	}

	printf("Complete\n"); //prints complete after run is finished

	fclose(outputFile); //closes the file

	return EXIT_SUCCESS;
}
