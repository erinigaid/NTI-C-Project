/*
 ===================================================================================================
 Program     :Mini Library Management System
 Author      : Erini G
 Description : Perform Basic Library System Functions
 Date		 : 29/07/2022
 ===================================================================================================
 */


#include "main.h"


List_t *List1;	
u8 choice, element;
u8 nameReturn[STR_LEN], authorReturn[STR_LEN], priceReturn;



void main(void)
{	

	printf("---------------------- Welcome to the Library app ----------------------\n");
	CreateList(&List1);
	
	do{
		printf("\nChoose one of the following options:   \n");
		printf("To view all books               Enter '1'\n");
		printf("To add a New book               Enter '2'\n");
		printf("To Delete a book                Enter '3'\n");
		printf("To view No. of available books  Enter '4'\n");
		printf("To Exit the Library App         Enter '5'\n");
		
		printf("--------------------------------------------------------------------\n");
		
		printf("---> Your choice is: ");
		scanf("%d",&choice);
		
		switch(choice)
		{
			case 1:
				DisplayList(List1);
				printf("--------------------------------------------------------------------\n");
			break;
			
			case 2:
				fflush(stdin);
				
				printf("Enter the name of the book: ");
				gets(nameReturn);
				
				fflush(stdin);
				
				printf("Enter the name of the author: ");
				gets(authorReturn);
				
				fflush(stdin);
				
				printf("Enter the price of the book: ");
				scanf("%d",&priceReturn);
				
				fflush(stdin);
				
				AddToBack(List1,nameReturn,authorReturn,priceReturn);
				printf("--------------------------------------------------------------------\n");
			break;
			
			case 3:
				printf("Enter the book number to delete: ");
				scanf("%d",&element);
				
				RemoveFromList(List1, element);
				printf("--------------------------------------------------------------------\n");
			break;
			
			case 4:
				CountList(List1);
			break;
			
			case 5:
			printf("Goodbye!\n");
			exit(0);
			break;
			
			default:
				printf("You Entered a Wrong Choice\n");
				
			break;
		}
	}
	while(choice!=5);
}