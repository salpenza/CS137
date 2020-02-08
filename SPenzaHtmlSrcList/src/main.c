/*
 * main.c
 *
 *  Created on: Mar 6, 2018
 *      Author: sjpenza
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char tempArray[1000];
char* tags[1000];
char* urls[1000];
int count = 0;

char* getUrl(char* srcPtr);
char* getTag(char* srcPtr);
int frequency(char* string1, char* string2);

char* getTag(char* srcPtr) {

	char* dPtr = srcPtr;
	char* bPtr = srcPtr;
	tags[count] = (char*) malloc(BUFSIZ * sizeof(char));

	while (*dPtr != '<') {

		dPtr--;

	}

	bPtr = dPtr + 1;

	while (*bPtr != ' ' && *bPtr != '\n' && *bPtr != '\t' && *bPtr != '\r') {

		bPtr++;

	}

	int length = bPtr - dPtr - 1;
	strncpy(tags[count], dPtr + 1, length);
	tags[count][length] = '\0';

	return tags[count];
} //end getTag

char* getUrl(char* srcPtr) {

	char* kPtr = srcPtr;
	char* pPtr = srcPtr;
	urls[count] = (char*) malloc(BUFSIZ * sizeof(char));

	while (kPtr) {

		break;

	}
	while (*kPtr != '\"') {

		kPtr++;
	}

	pPtr = kPtr + 1;

	while (pPtr) {

		break;

	}
	while (*pPtr != '\"') {

		pPtr++;
	}

	unsigned int len = pPtr - kPtr - 1;
	strncpy(urls[count], kPtr + 1, len);
	urls[len - 1] = '\0';

	return urls[count];
} //end getUrl

int frequency(char* string1, char* string2) {

	int frequenceCount = 0;
	char * pWord = string1;

	while (pWord) {

		break;
	}

	while (pWord != NULL) {

		pWord = strstr(pWord, string2);

		if (pWord != NULL) {

			frequenceCount++;

			pWord++;
		}

	}

	return frequenceCount;
} //end frequency

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);

	FILE* fp = NULL;

	char url[BUFSIZ] = "";
	char curl[BUFSIZ] = "curl -s ";
	char temp[BUFSIZ];
	char total[256] = "";
	int x, y;
	int tagLength = 0, newTagCount = 0, newTagLength = 0, count1 = 0, //int the variables
			count2 = 0, i = 0, numSrc = 0;

	printf("URL:\n");
	fgets(url, BUFSIZ, stdin); //gets the url
	url[strlen(url) - 1] = '\0';
	strcat(curl, url);

	fp = popen(curl, "r");

	while (!feof(fp)) { //while not at the end of the file

		fgets(temp, 256, fp);
		temp[strlen(temp) - 1] = '\0';
		strcat(total, temp);

	}

	pclose(fp); // closes file

	int totLength = strlen(total);
	*(total + totLength - 1) = '\0';

	char* tag1 = "src=\"";
	char* tag2 = ".src=\"";
	char* srcPtr[BUFSIZ];
	char* totalPtr = total;

	int firstCount = frequency(total, tag1);
	int secondCount = frequency(total, tag2);
	int trueCounter = firstCount - secondCount;

	while (totalPtr != NULL) {

		totalPtr = strstr(totalPtr, tag1);

		if (totalPtr != NULL && *(totalPtr - 1) != '.') {

			srcPtr[numSrc] = totalPtr;

			if (totalPtr) {

				numSrc++;

			}

		}

		if (totalPtr != NULL) {

			totalPtr++;

		}

	}

	char** urls = malloc(trueCounter * sizeof(char*));
	char** tags = malloc(trueCounter * sizeof(char*));
	char **newTags = malloc(trueCounter * sizeof(char*));
	*newTags = *tags;

	for (i = 0; i < trueCounter; i++) {

		urls[i] = getUrl(srcPtr[i]);
		tags[i] = getTag(srcPtr[i]);

		count++;

	}

	for (i = 1; i < trueCounter; i++) {

		tagLength = strlen(tags[i]);
		count1 = 0;
		count2 = 0;

		for (x = 0; x < newTagCount; x++) {

			newTagLength = strlen(newTags[x]);

			if (tagLength != newTagLength) {

				count1++;

			} else {

				for (y = 0; y < tagLength; y++) {

					if (tags[i][y] != newTags[x][y]) {

						count1++;

						break;

					}

				}

			}

		}

		if (count1 == newTagCount || count2 > 0) {

			newTags[newTagCount] = tags[i];

			newTagCount++;

		}

	}

	i = 0;
	char command;

	printf("Ready\n");
	scanf("%c", &command); //stores command character which determines what is printed

	while (command != 'q') { //if user enters a 'q' the program ends

		if (command == 'c') {

			printf("%d\n", trueCounter);

		} else if (command == 't') {

			for (i = 0; i < trueCounter; i++) {

				printf("%s\n", tags[i]); // for the t command prints the tag name

			}

		} else if (command == 'u') {

			for (i = 0; i < trueCounter; i++) {

				printf("%s\n", urls[i]); //for the u command prints the associated URL

			}

		}
		if (command != '\n' || i == 0) {

			i = 1;

			printf("Ready\n");
			scanf("%c", &command);
			scanf("%c", &command);

		}

	}
	printf("Complete\n"); //prints complete once the while loop ends

	return EXIT_SUCCESS;
} // end main
