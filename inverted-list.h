#ifndef INVERTED_LIST_H
#define INVERTED_LIST_H

typedef struct	stringStruct	{	char*					string;		} stringStruct;
		typedef	stringStruct*											  stringStructPtr;
		typedef stringStruct 											  tokenStr;
		typedef tokenStr* 												  tokenPtr;
		typedef stringStruct 											  filePath;
		typedef filePath*												  filePathPtr;
		typedef stringStruct											  fileContents;
		typedef fileContents*											  fileContentsPtr;
	
typedef struct fileList			{ 	filePathPtr				 path; 
									struct fileList* 		 next;		} fileList;		
		typedef fileList* 											      fileListPtr;
		
typedef struct wordList
{
	char* token;
	struct wordList *next;
} wordList;
typedef wordList* wordListPtr;
		
typedef struct tokenList		{   tokenPtr				 token;
									filePathPtr				 path;		
									struct tokenList*		 next;		} tokenList;
		typedef	tokenList*  											  tokenListPtr;
				
typedef struct	referenceList	{ 	filePathPtr				 path;
									int*					 freq;
									int fuckYou;
									struct referenceList*	 next;		} referenceList;
		typedef referenceList* 										  	  referenceListPtr;

typedef struct 	InvertedList	{ 	tokenPtr				 token;
									referenceListPtr		 fileDetails;
									struct InvertedList*	 next;		} InvertedList;
		typedef InvertedList* 										      InvertedListPtr; 

typedef struct container
{
	char				*path;
	char				*token;
	struct container*	next;
}container;
typedef struct fileNode
{
	char				*path;
	int					freq;
	struct fileNode		*next;
} fileNode;
typedef fileNode* fileNodePtr;

typedef struct ILNode
{
	char				*token;
	fileNode 			*pathData;
	struct ILNode		*next;
} ILNode;
typedef ILNode* ILNodePtr;



stringStructPtr		stringStructCreate		( char*				string							);
int					stringStructDestroy		( stringStructPtr	ptr								);
tokenListPtr		tokenListCreate			( 													);
int					tokenListDestroy		( tokenListPtr	  	ptr								);
fileListPtr			fileListCreate			( 	char* string												);
int					fileListDestroy			( fileListPtr	 	ptr								);
referenceListPtr	referenceListCreate		( 													);
int					referenceListDestroy	( referenceListPtr 	ptr								);
InvertedListPtr 	ILCreate				( 													);
int					ILDestroy				( InvertedListPtr	list							);


int tokenSearch(ILNode *head, char* token, char* path);



void printTokens(ILNode *head);
void pathSearch(ILNode *head, char* file);
int ILPrint(ILNode *head);
int readDir(char* file, container **head);
int newList(ILNode **head, container *ptr);
void mergeSort(ILNode **head);
void mergeSplit(ILNode* head, ILNode** back, ILNode** front);
ILNode* SortedMerge(ILNode* a, ILNode *b);
void mergeSortRecords(fileNode **recordList);
fileNode* SortedMergeRecords(fileNode* a, fileNode *b);
void mergeSplitRecords(fileNode* head, fileNode**back, fileNode** front);

#endif
