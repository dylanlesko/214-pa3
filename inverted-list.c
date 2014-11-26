#include "headers.h"

stringStructPtr stringStructCreate ( char* string )
{
	stringStructPtr newStruct = (stringStructPtr)malloc(sizeof(stringStruct));
		
	if(string == NULL)
	{
		newStruct->string = NULL;
		return newStruct;
	}
	
	newStruct->string = malloc ( strlen ( string ) + 1);
		strcpy(newStruct->string, string);
		(newStruct->string)[strlen(string)] = '\0';
		
	return newStruct;
}
void buildList(ILNode **head, container *ptr)
{

	if ( (*head) == NULL )
	{
		(*head) = malloc(sizeof(ILNode));
			(*head)->token = malloc(strlen(ptr->token)+1);
				strcpy((*head)->token, ptr->token);
			(*head)->pathData = malloc(sizeof(fileNode));
				(*head)->pathData->path = malloc( strlen( ptr->path ) + 1);
					strcpy( ((*head)->pathData->path), ptr->path);
			(*head)->pathData->freq = 1;
			(*head)->next = NULL;
	}
	else
	{
		fileNode *pathIter;
		ILNode *tokenIter;
		tokenIter = (*head);
		pathIter = tokenIter->pathData;
		
		//token loop
		while(tokenIter->next != NULL)
		{
			pathIter = tokenIter->pathData;
			//new token
			if ( strcmp ( ptr->token, tokenIter->token) != 0 )
			{
				tokenIter = tokenIter->next;
				pathIter = tokenIter->pathData;
			}
			//existing token
			else
			{
				//path loop
				while ( pathIter->next != NULL)
				{
					//new path
					if ( strcmp ( ptr->path, pathIter->path) != 0 )
					{
						pathIter = pathIter->next;
					}
					//existing path
					else
					{
						pathIter->freq += 1;
						return;
					}
				}//end path loop
				//made it out of path loop
				//same token, no path match, add path to token
					if( strcmp ( ptr->path, pathIter->path) != 0 )
					{
						pathIter->next = malloc(sizeof(fileNode));
						pathIter->next->path = malloc(strlen( ptr->path ) + 1);
							strcpy(pathIter->next->path, ptr->path);
						pathIter->next->freq = 1;
						pathIter->next->next = NULL;
					return;
					}
					else
					{
						pathIter->freq += 1;
						return;
					}
			}			
			
		}//end token loop
		//made it out of token loop
		//different token, add token to list
		if ( strcmp ( ptr->token, tokenIter->token) != 0)
		{
			tokenIter->next = malloc(sizeof(ILNode));
			tokenIter->next->token = malloc(strlen(ptr->token) + 1);
				strcpy(tokenIter->next->token, ptr->token);
			tokenIter->next->next = NULL;
			tokenIter->next->pathData = malloc(sizeof(fileNode));
			tokenIter->next->pathData->path = malloc(strlen(ptr->path) + 1);
				strcpy(tokenIter->next->pathData->path, ptr->path);
			tokenIter->next->pathData->freq = 1;
			tokenIter->next->pathData->next = NULL;	
		}
		else
		{
			while( pathIter->next != NULL )
			{
				if ( strcmp ( ptr->path, pathIter->path) != 0)
				{
					pathIter = pathIter->next;
				}
				else
				{
					pathIter->freq += 1;
					return;
				}
			}
			pathIter->freq += 1;

			
		}
	}
}


void mergeSort(ILNode **ILList)
{
	ILNode *head = *ILList;
	ILNode *a;
	ILNode *b;
	
	if ((head == NULL) || (head->next == NULL))
	{
		return;
	}
	
	mergeSplit(head, &a, &b);
	
	mergeSort(&a);
	mergeSort(&b);
	
	*ILList = SortedMerge(a, b);
	
}
ILNode* SortedMerge(ILNode* a, ILNode *b)
{
	ILNode *result = NULL;
	
	if (a == NULL)
		return b;
	else if(b== NULL)
			return a;
			
	if( strcmp(a->token, b->token) < 0)
	{
		result = a;
		result->next = SortedMerge(a->next, b);
	}
	else
	{
		result = b;
		result->next = SortedMerge(a,b->next);
	}
	return result;
	
}
void mergeSplit(ILNode* head, ILNode** back, ILNode** front)
{
	ILNode* fast;
	ILNode* slow;
	
	if((head == NULL) || (head->next == NULL))
	{
		*front = head;
		back = NULL;
	}
	else
	{
		slow = head;
		fast = head->next;
		
		while(fast != NULL)
		{
			fast = fast->next;
			if(fast != NULL)
			{
				slow = slow->next;
				fast = fast->next;
			}
		}
		
		*front = head;
		*back = slow->next;
		slow->next = NULL;
	}
}


void mergeSortRecords(fileNode **recordList)
{
	fileNode *head = *recordList;
	fileNode *a;
	fileNode *b;
	if ((head == NULL) || (head->next == NULL))
	{
		return;
	}
	mergeSplitRecords(head, &a, &b);
	mergeSortRecords(&a);
	mergeSortRecords(&b);
	*recordList = SortedMergeRecords(a, b);
}
fileNode* SortedMergeRecords(fileNode* a, fileNode *b)
{
	fileNode *result = NULL;
	
	if (a == NULL)
		return b;
	else if(b== NULL)
			return a;
			
	if( (a->freq > b->freq) )
	{
		result = a;
		result->next = SortedMergeRecords(a->next, b);
	}
	else
	{
		result = b;
		result->next = SortedMergeRecords(a,b->next);
	}
	return result;
	
}
void mergeSplitRecords(fileNode* head, fileNode**back, fileNode** front)
{
	fileNode* fast;
	fileNode* slow;
	
	if((head == NULL) || (head->next == NULL))
	{
		*front = head;
		back = NULL;
	}
	else
	{
		slow = head;
		fast = head->next;
		
		while(fast != NULL)
		{
			fast = fast->next;
			if(fast != NULL)
			{
				slow = slow->next;
				fast = fast->next;
			}
		}
		
		*front = head;
		*back = slow->next;
		slow->next = NULL;
	}	
	

}


int ILPrint(ILNode *head)
{
	ILNode *fileIter = head;
	fileNode *pathIter;
	
	while(fileIter != NULL)
	{
		pathIter = fileIter->pathData;
		printf("\n%s", fileIter->token);
		while(pathIter != NULL)
		{
			printf("\n\t%s\t\t%d", pathIter->path, pathIter->freq);
			pathIter = pathIter->next;
		}
		fileIter = fileIter->next;	
	}	
}
int tokenSearch(ILNode *head, char* token, char* path)
{
	ILNode *tokenIter = head;
	fileNode *pathIter = head->pathData;
	
	
	while(tokenIter != NULL)
	{
		if( strcmp( ( tokenIter->token ), token ) == 0 )
		{
			while(pathIter != NULL)
			{
				if(strcmp((pathIter->path), path) == 0)
				{			
					printf("\nfound: %s", token);
					printf("\nfound: %s", path);
					return 0;
				}
				pathIter = pathIter->next;
			}
			
			return 1;
		}
		tokenIter = tokenIter->next;
	}
}
