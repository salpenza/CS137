/*
 * address_book.h
 *
 *  Created on: May 9, 2018
 *      Author: sjpenza
 */

#ifndef ADDRESS_BOOK_H_
#define ADDRESS_BOOK_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct listNode { //structure for contacts
    char lastName[255];
    char firstName[255];
    char emailAddress[255];
    char phoneNumber[255];
    struct listNode *next;
} ListNode;

typedef ListNode *ListNodePtr; //structure pointer
//function declarations
void add(ListNode ** pB, ListNode userNode, int firstSpot);
void delete(ListNode ** pB, int firstSpot);
ListNodePtr getContact(ListNode **pB, int firstSpot);
void numContacts(ListNode ** pB, int * pContacts);
int isEmpty(ListNodePtr pB);
void create(ListNodePtr pRoot);
void swap( ListNodePtr *pDB, int index1, int index2 );

#endif /* ADDRESS_BOOK_H_ */

