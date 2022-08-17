#ifndef LIBRARY_H
#define LIBRARY_H


#include <stdio.h>
#include <stdlib.h>
#include "STD_TYPES.h"
#include "ERROR_STATE.h"


#define STR_LEN 30

typedef struct Book
{
	u8 BookName[STR_LEN];
	u8 AuthorName[STR_LEN];
	u8 Price;
	
}Book_t;

typedef struct Node
{
	struct Node *Next;
	struct Node *Previous;
	Book_t BookInfo;
	
}Node_t;

typedef struct List
{
	u8 Size;
	Node_t *Head;
	Node_t *Tail;
	
}List_t;

typedef enum
{
	LIST_EMPTY,
	LIST_NEMPTY
	
}ListState_t;



/*-------------------------Function Prototype-------------------------*/
u8 str_cpy(u8 OrgStr[],u8 CpyStr[]);

ErrorState_t CreateList(List_t **ListAddress);
static ErrorState_t List_Empty(List_t *List, ListState_t *ListState);
ErrorState_t AddToBack(List_t *List, u8 BookName_F[], u8 AuthorName_F[], u8 Price_f);
ErrorState_t DisplayList(List_t *List);
ErrorState_t CountList(List_t *List);
ErrorState_t RemoveFromList(List_t *List, u8 index);



#endif