/*-------------------------Sub-Program-------------------------*/


#include "library.h"

/*Copy contents of array into another array*/
u8 str_cpy(u8 OrgStr[],u8 CpyStr[])
{
	for(u8 i = 0;i < STR_LEN;i++)
	{
		CpyStr[i] = OrgStr[i];
	}
}



/*Create a doubly linked list*/
ErrorState_t CreateList(List_t **ListAddress)
{
	//Check Function execution state
	ErrorState_t ReturnState = RET_OK; 
	//Check the entered ptr = null
	if(NULL == ListAddress)
	{
		ReturnState = RET_NULL_PTR;
	}
	else
	{
		//allocate the list and size dynamically
		List_t *ListPtr = (List_t *) malloc(sizeof(List_t));
		//Check if the allocation succeded
		if(NULL == ListPtr)
		{
			ReturnState = RET_NULL_PTR;
		}
		else
		{
			//initilize the struct members
			ListPtr->Size = 0;
			ListPtr->Head = NULL;
			ListPtr->Tail = NULL;
			//return the address of the new list
			*ListAddress = ListPtr;
			//printf("List created");
		}
	}
	return ReturnState;
}


/*Check if the list is empty and resturn the state*/
static ErrorState_t List_Empty(List_t *List, ListState_t *ListState)
{
	ErrorState_t ReturnState = RET_OK; 
	if((NULL == List) || (NULL == ListState))
	{
		ReturnState = RET_NULL_PTR;
	}
	else
	{
		//Check if size = 0 then list is empty else not empty
		if(0 == List->Size)
		{
			*ListState = LIST_EMPTY;
		}
		else
		{
			*ListState = LIST_NEMPTY;
		}
	}
	return ReturnState;
}


/*Add new node to the list*/
ErrorState_t AddToBack(List_t *List, u8 BookName_F[], u8 AuthorName_F[], u8 Price_f)
{
	ErrorState_t ReturnState = RET_OK;
	ListState_t ListStateReturn = LIST_NEMPTY;

	if(NULL == List)
	{
		ReturnState = RET_NULL_PTR;
	}
	else
	{
		//allocating the node and size dynamically
		Node_t *NodePtr = (Node_t *)malloc(sizeof(Node_t));
		if(NULL == NodePtr)
		{
			ReturnState = RET_NULL_PTR;
		}
		else
		{
			//storing the entered data into the node
			str_cpy(BookName_F, NodePtr->BookInfo.BookName);
			str_cpy(AuthorName_F, NodePtr->BookInfo.AuthorName);
			NodePtr->BookInfo.Price = Price_f;
			//add to the back so Next is NULL
			NodePtr->Next = NULL; 
			//Calling function to check list
			List_Empty(List, &ListStateReturn);
			//List is Empty
			if(LIST_EMPTY == ListStateReturn)
			{
				//1st node so head & tail pointing at the new node 
				List->Head = NodePtr;
				List->Tail = NodePtr;
				NodePtr->Previous = NULL;
				printf("Book Added Successfully.\n");
			}
				//List not Empty
			else
			{
				//New Tail Added
				List->Tail->Next = NodePtr;
				NodePtr->Previous = List->Tail;
				List->Tail = NodePtr;
				printf("Book Added Successfully.\n");
			}
			List->Size++;
			
		}
	}
	return ReturnState;
}


/*Display the Values in the List*/
ErrorState_t DisplayList(List_t *List)
{
	ErrorState_t ReturnState = RET_OK;
	ListState_t ListStateReturn = LIST_NEMPTY;
	
	if(NULL == List)
	{
		ReturnState = RET_NULL_PTR;
	}
	else
	{
		List_Empty(List, &ListStateReturn);
		if(LIST_EMPTY == ListStateReturn)
		{
			printf("Book List is Empty.\n");
		}
		else
		{
			//ptr to 1st node 
			Node_t *CurrentNode = List->Head;
			if(NULL == CurrentNode)
			{
				ReturnState = RET_NULL_PTR;
			}
			else{
				printf("\n------------------------ The Available Books ------------------------\n\n");
				//looping through the list till the last node
				int i=1;
				while(NULL != CurrentNode)
				{
					printf("Book No. %d: \n",i);
					printf("Book name: %s\n",CurrentNode->BookInfo.BookName);
					printf("Author name: %s\n",CurrentNode->BookInfo.AuthorName);
					printf("price: %d\n",CurrentNode->BookInfo.Price);
					
					//move to the next node
					CurrentNode = CurrentNode->Next;
					
					printf("\n--------------------------------------------------------------------\n");
					i++;

				}
			}			
		}
	}
	return ReturnState;
}


/*Count the Node in the List*/
ErrorState_t CountList(List_t *List)
{
	ErrorState_t ReturnState = RET_OK;
	ListState_t ListStateReturn = LIST_NEMPTY;
	
	if(NULL == List)
	{
		ReturnState = RET_NULL_PTR;
	}
	else
	{
		List_Empty(List, &ListStateReturn);
		if(ListStateReturn == LIST_EMPTY)
		{
			printf("Book List is Empty.\n");
		}
		else
		{
			printf("Number of books in the library: %d\n",List->Size);
		}
	}
	return ReturnState;
}


/*Delete Node from list at a specific index*/
ErrorState_t RemoveFromList(List_t *List, u8 index)
{
	ErrorState_t ReturnState = RET_OK;
	ListState_t ListStateReturn = LIST_NEMPTY;
	if(NULL == List)
	{
		ReturnState = RET_NULL_PTR;
	}

	else
	{
		List_Empty(List, &ListStateReturn);
		if(LIST_EMPTY == ListStateReturn)
		{
			printf("Book List is Empty.\n");
		}
		
		//index doesn't exist
		else if(index > List->Size || 0 >= index )
		{
			printf("Book No. %d doesn't exist.\n",index);
		}
		

		else
		{
			//only one element in the list
			if(1 == List->Size)
			{
				free(List->Head);
				List->Head = NULL;
				List->Tail = NULL;
				printf("Book Deleted Successfully.\n");
			}
			
			//delete head
			else if (1 == index)
			{
				List->Head = List->Head->Next;
				free(List->Head->Previous);
				List->Head->Previous = NULL;
				printf("Book Deleted Successfully.\n");
			}
			//delete tail
			else if (List->Size == index)
			{
				List->Tail = List->Tail->Previous;
				free(List->Tail->Next);
				List->Tail->Next = NULL;
				printf("Book Deleted Successfully.\n");
			}
			
			//delete specific node
			else
			{
				//ptr to head node
				Node_t *CurrentNode = List->Head;
				if(NULL == CurrentNode)
				{
					ReturnState = RET_NULL_PTR;
				}
				else
				{
					//counter to the node's number
					u8 CurrentCount = 1;
					//checking that the current node is not null and the counter is less than or equal the entered index
					while(NULL != CurrentNode && CurrentCount <= index)
					{
						// current node count equal the enter index
						if(CurrentCount == index)
						{
							
							//temp to store the current node
							Node_t *temp = CurrentNode;
							
							CurrentNode->Previous->Next = CurrentNode->Next;
							CurrentNode->Next->Previous = CurrentNode->Previous;
							
							//the current node is the next of the old current 
							CurrentNode = temp->Next;
							
							//delete the old current
							free(temp);
							printf("Book Deleted Successfully.\n");							
						}						
						else{}
						
						//Current Node++ to check the next node
						CurrentNode = CurrentNode->Next;
						//counter++ to check if the next node number equal the index
						CurrentCount++;
						
						
						
						
					}
				}
			}
			
			List->Size--;
					
		}
	}
	return ReturnState;
}


