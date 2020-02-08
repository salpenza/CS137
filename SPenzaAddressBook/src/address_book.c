/*
 * address_book.c
 *
 *  Created on: May 9, 2018
 *      Author: sjpenza
 */

#include "address_book.h"

void add(ListNode ** sPtr, ListNode userNode, int firstSpot) {
	int i;
	ListNodePtr pNew; // points to the new node
	ListNodePtr pPrev; // points to previous node
	ListNodePtr pCurr; //points to current node
	pPrev = NULL;
	pCurr = *sPtr;
	pNew = malloc(sizeof(ListNode)); // creates node
	if (pNew != NULL) {

		strcpy(pNew->lastName, userNode.lastName);
		strcpy(pNew->firstName, userNode.firstName);
		strcpy(pNew->emailAddress, userNode.emailAddress);
		strcpy(pNew->phoneNumber, userNode.phoneNumber);
		pNew->next = NULL;

		for (i = 0; i < firstSpot && pCurr != NULL; i++) { //find location in list
			pPrev = pCurr;
			pCurr = pCurr->next;
		}

		if (firstSpot == 0) {
			pNew->next = *sPtr;
			*sPtr = pNew;
		} else {
			pPrev->next = pNew;
			pNew->next = pCurr;
		}
	} else {
		printf("address not inserted. No memory available.\n");
	}
} //end insert function

void delete(ListNode ** sPtr, int firstSpot) {
	int i;
	ListNodePtr pPrev; // points to previous node
	ListNodePtr pCurr; // points to current node
	ListNodePtr ptemp;

	if (firstSpot == 0) { // deletes first node
		ptemp = *sPtr;
		*sPtr = (*sPtr)->next;
		free(ptemp);
	} else {
		pPrev = *sPtr;
		pCurr = (*sPtr)->next;

		for (i = 0; i < firstSpot - 1 && pCurr != NULL; i++) { // finds where firstSpot points
			pPrev = pCurr;
			pCurr = pCurr->next;
		}

		if (pCurr != NULL) { // deletes node
			ptemp = pCurr;
			pPrev->next = pCurr->next;
			free(ptemp);
		}
	}
} //end of delete function

ListNodePtr getContact(ListNode **sPtr, int firstSpot) {
	int i;
	ListNodePtr pCurr; // points to current node
	pCurr = *sPtr;

	for (i = 0; pCurr != NULL && i < firstSpot; i++) {
		pCurr = pCurr->next;
	}
	return pCurr;
} //end getContact function

void numContacts(ListNode ** pB, int * pContacts) {
	int i;
	ListNodePtr pCurr; // points to current node
	pCurr = *pB;

	for (i = 0; pCurr != NULL; i++) {
		pCurr = pCurr->next;
	}
	if (pContacts != NULL) {
		*pContacts = i;
	}
} //end numContacts

int isEmpty(ListNodePtr pB) {
	return pB == NULL;
} // end function isEmpty

void create(ListNodePtr pRoot) {
	int k, p, firstIndex, listCount;
	int minCount = 0;
	int minIndex = 0;
	ListNodePtr pOpen = NULL;
	ListNodePtr pMin = NULL;
	ListNodePtr pCount = NULL;
	ListNodePtr pTemp = NULL;
	numContacts(&pRoot, &listCount);

	for (firstIndex = 0; firstIndex < listCount; firstIndex++) {
		pOpen = getContact(&pRoot, firstIndex);

		for (k = firstIndex; k < listCount; k++) {
			pMin = getContact(&pRoot, minIndex);
			pCount = getContact(&pRoot, k);

			if (k == firstIndex) {
				minIndex = firstIndex;
			}

			if (strcmp(pMin->lastName, pCount->lastName) > 0) {
				minIndex = k;
				pMin = getContact(&pRoot, minIndex);
			}
		}

		minCount = 0;
		for (p = firstIndex; p < listCount; p++) { //find minimums in lastName
			pTemp = getContact(&pRoot, p);

			if (strcmp(pTemp->lastName, pMin->lastName) == 0) {
				minCount++;
			}
		}

		if (minCount > 1) { //find minimums in firstName, emailAddress, and phoneNumber

			for (k = firstIndex; k < listCount; k++) {
				pMin = getContact(&pRoot, minIndex);
				pCount = getContact(&pRoot, k);

				if (k == firstIndex) {
					minIndex = firstIndex;
				}

				if (strcmp(pMin->phoneNumber, pCount->phoneNumber) > 0) {
					minIndex = k;
					pMin = getContact(&pRoot, minIndex);
				}
			}
		}
		if (minCount > 1) {

			for (k = firstIndex; k < listCount; k++) {
				pMin = getContact(&pRoot, minIndex);
				pCount = getContact(&pRoot, k);

				if (k == firstIndex) {
					minIndex = firstIndex;
				}

				if (strcmp(pMin->firstName, pCount->firstName) > 0) {
					minIndex = k;
					pMin = getContact(&pRoot, minIndex);
				}
			}

			minCount = 0;
			for (p = firstIndex; p < listCount; p++) {
				pTemp = getContact(&pRoot, p);

				if (strcmp(pTemp->firstName, pMin->firstName) == 0) {
					minCount++;
				}
			}

			if (minCount > 1) {

				for (k = firstIndex; k < listCount; k++) {
					pMin = getContact(&pRoot, minIndex);
					pCount = getContact(&pRoot, k);

					if (k == firstIndex) {
						minIndex = firstIndex;
					}

					if (strcmp(pMin->emailAddress, pCount->emailAddress) > 0) {
						minIndex = k;
						pMin = getContact(&pRoot, minIndex);
					}
				}

				minCount = 0;
				for (p = firstIndex; p < listCount; p++) {
					pTemp = getContact(&pRoot, p);

					if (strcmp(pTemp->emailAddress, pMin->emailAddress) == 0) {
						minCount++;
					}
				}

			}
		}

		swap(&pRoot, minIndex, firstIndex);
	}
} // end function organize

void swap(ListNodePtr* pDB, int index1, int index2) {
	ListNodePtr pNode1 = getContact(pDB, index1);
	ListNodePtr pNode2 = getContact(pDB, index2);
	ListNode temp;

	strcpy(temp.lastName, pNode1->lastName);
	strcpy(temp.firstName, pNode1->firstName);
	strcpy(temp.emailAddress, pNode1->emailAddress);
	strcpy(temp.phoneNumber, pNode1->phoneNumber);

	strcpy(pNode1->lastName, pNode2->lastName);
	strcpy(pNode1->firstName, pNode2->firstName);
	strcpy(pNode1->emailAddress, pNode2->emailAddress);
	strcpy(pNode1->phoneNumber, pNode2->phoneNumber);

	strcpy(pNode2->lastName, temp.lastName);
	strcpy(pNode2->firstName, temp.firstName);
	strcpy(pNode2->emailAddress, temp.emailAddress);
	strcpy(pNode2->phoneNumber, temp.phoneNumber);
}

