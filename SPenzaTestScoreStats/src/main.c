/*
 * main.c
 *
 *  Created on: Feb 6, 2018
 *      Author: sjpenza
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);

	float average, standDev = 0, max = 0, min = 101, sum = 0, sumsquared = 0,
			sumofsquares = 0, num = 0;
	int count = 0;
	int end = 0;
	char buffer[BUFSIZ + 1];
	printf(
			"Enter scores, one per line.  Press <ENTER> on a blank line to end.\n");

	do {
		//scanf("%d", &num);
		num = atof(fgets(buffer, BUFSIZ, stdin));
		if (buffer[0] == '\n') {
			if(count==0){
				min = 0;
			}
			break;
		}
		//fgets(buffer, BUFSIZ, stdin);
		count++;
		sum = sum + num;
		average = 1.0 * sum / count;
		sumsquared = sum * sum;
		sumofsquares += num * num;

		if (num > max)
			max = num;
		if (num < min)
			min = num;

		standDev = sqrt((sumofsquares - sumsquared / count) / count);
	} while (end != 1);

	printf("%d\t%f\t%f\t%f\t%f\n", count, min, max, average, standDev);
	return EXIT_SUCCESS;
}

