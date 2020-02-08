/*
 * main.c
 *
 *  Created on: May 9, 2018
 *      Author: sjpenza
 */
#include "address_book.h"

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
	//printf("Ready\n");
	//scan
	int firstParameter, contactCount, count; // initialize variables for main
	char secondParameter[255] = "second";
	char thirdParameter[255] = "third";
	char userAddressInput[1000];
	char inputFilename[1000];
	char outputFilename[1000];
	char temp[255 * 4 + 3];
	char command;

	FILE *pIFile = NULL;
	FILE *pOFile = NULL;

	ListNodePtr pStart = NULL;
	ListNode location;
	ListNodePtr pContact;

	printf("Ready\n");
	scanf("%c", &command); // print Ready and scan for the given command by the user

	while (command != 'q') {
		switch (command) { // switch statement that determines what to execute by whatever char the user entered

		case '\n':
			do {
				scanf("%c", &command);
			} while (command == '\n');
			break;
		case 'a':
			do {
				scanf("%u", &firstParameter);
				scanf("%s", userAddressInput);
			} while (firstParameter == '\n');
			int a = (int) strlen(userAddressInput);
			userAddressInput[a] = '\0';
			strcpy(location.lastName, strtok(userAddressInput, ","));
			strcpy(location.firstName, strtok(NULL, ","));
			strcpy(location.emailAddress, strtok(NULL, ","));
			strcpy(location.phoneNumber, strtok(NULL, ","));

			add(&pStart, location, firstParameter);
			break;
		case 'd':
			numContacts(&pStart, &contactCount);
			if (contactCount != 0) {
				scanf("%u", &firstParameter);
				delete(&pStart, firstParameter);
			}
			break;
		case 'e':
			scanf("%u", &firstParameter);
			pContact = getContact(&pStart, firstParameter);

			scanf("%s", secondParameter);
			secondParameter[strlen(secondParameter)] = '\0';

			scanf("%s", thirdParameter);
			thirdParameter[strlen(thirdParameter)] = '\0';
			while(firstParameter != NULL){
				break;
			}
			if (strcmp(secondParameter, "lastName") == 0) {
				strcpy(pContact->lastName, thirdParameter);
			} else if (strcmp(secondParameter, "firstName") == 0) {
				strcpy(pContact->firstName, thirdParameter);
			} else if (strcmp(secondParameter, "email") == 0) {
				strcpy(pContact->emailAddress, thirdParameter);
			} else if (strcmp(secondParameter, "phoneNumber") == 0) {
				strcpy(pContact->phoneNumber, thirdParameter);
			}
			break;
		case 'f':
			scanf("%u", &firstParameter);
			pContact = getContact(&pStart, firstParameter);
			scanf("%s", secondParameter);
			secondParameter[strlen(secondParameter)] = '\0';
			if (strcmp(secondParameter, "lastName") == 0) {
				printf("%s\n", pContact->lastName);
			} else if (strcmp(secondParameter, "firstName") == 0) {
				printf("%s\n", pContact->firstName);
			} else if (strcmp(secondParameter, "email") == 0) {
				printf("%s\n", pContact->emailAddress);
			} else if (strcmp(secondParameter, "phoneNumber") == 0) {
				printf("%s\n", pContact->phoneNumber);
			}
			break;
		case 'g':
			scanf("%u", &firstParameter);
			pContact = getContact(&pStart, firstParameter);
			printf("%s,%s,%s,%s\n", pContact->lastName, pContact->firstName,
					pContact->emailAddress, pContact->phoneNumber);
			break;
		case 'l':
			do {
				fgets(inputFilename, BUFSIZ, stdin);
			} while (inputFilename[0] == '\n');
			int inNameLength = strlen(inputFilename);
			inputFilename[inNameLength - 1] = '\0';

			pIFile = fopen(inputFilename, "r");

			if (pIFile == NULL) {
				printf("File could not be opened.\n");
			} else {
				do {
					fgets(temp, 1050, pIFile);
				} while (temp[0] == '\n');
				while (fgets(temp, 1050, pIFile)) {
					int numcontacts = 0;
					numContacts(&pStart, &numcontacts);
					temp[strlen(temp) - 1] = '\0';
					ListNode address;
					strcpy(address.lastName, strtok(temp, ","));
					strcpy(address.firstName, strtok(NULL, ","));
					strcpy(address.emailAddress, strtok(NULL, ","));
					strcpy(address.phoneNumber, strtok(NULL, ","));
					add(&pStart, address, numcontacts);
				}
			}
			break;
		case 'n':
			numContacts(&pStart, &contactCount);
			printf("%d\n", contactCount);
			break;
		case 'o':
			create(pStart);
			break;
		case 's':
			do {
				fgets(outputFilename, BUFSIZ, stdin);
			} while (outputFilename[0] == '\n');
			int i;
			int outputFilenameLength = strlen(outputFilename);
			outputFilename[outputFilenameLength - 1] = '\0';
			pOFile = fopen(outputFilename, "w");
			pContact = getContact(&pStart, 0);

			fprintf(pOFile, "lastName,firstName,email,phoneNumber\n");
			for (i = 0; pContact->next != NULL; i++) {

				pContact = getContact(&pStart, i);
				fprintf(pOFile, "%s,%s,%s,%s\n", pContact->lastName,
						pContact->firstName, pContact->emailAddress,
						pContact->phoneNumber);
			}
			break;
		}
		do {
			scanf("%c", &command);
		} while (command == '\n');

		count = 1;

	}
	printf("Complete\n");

	return EXIT_SUCCESS; //end
}
