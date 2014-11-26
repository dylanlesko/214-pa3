#include "headers.h"

int indexFiles ( filePathPtr path, fileList **filePaths, fileList **dirPaths )
{
	if ( path == NULL )
	{
		return 1;
	}
	
	if ( strlen( path->string ) > 2047)
	{
		printf("\nFile Path Length is Too Long.\n\n");
		exit(1);
		return 1;
	}
	
	
	DIR *dir;
	struct dirent *entry;
	int count = 0;
	
	
	//file
	if ( !( dir = opendir( path->string ) ) )
	{
		if ( (access ( path->string, F_OK ) == -1) || (access ( path->string, R_OK ) == -1))
		{
			printf("\nUnable to Open File: %s\n\n", path->string);
			closedir( dir );
			exit(1);
			return 1;
		}
		{
			if( (*filePaths) == NULL )
			{
				*filePaths = malloc(sizeof(fileList));
				(*filePaths)->path = malloc(sizeof(filePath));
				(*filePaths)->path->string = malloc(strlen(path->string) + 1 );
				strcpy( (*filePaths)->path->string, path->string );
				(*filePaths)->next = NULL;				
			}
			else
			{
				fileList *newFile;
				newFile = (*filePaths);
				
				while(newFile->next)
				{
					newFile = newFile->next;
				}					
				
				newFile->next = malloc(sizeof(fileList));
				newFile->next->path = malloc(sizeof(filePath));
				newFile->next->path->string = malloc(strlen(path->string) + 1 );
				strcpy( newFile->next->path->string, path->string );
				newFile->next->next = NULL;
			}
		}
		return 0;
	}
	
	//error
	if ( !(entry = readdir( dir ) ) )
	{
		return 1;
	}	
	//directory recursive retrieval
	do
	{	
		if ( (access ( path->string, F_OK ) == -1) || (access ( path->string, R_OK ) == -1))
		{
			closedir( dir );
			exit(1);
			return 1;
		}
		//dir
		if ( entry->d_type == DT_DIR )
		{
			//ignore ".." and "." listings
			if( ( strcmp( entry->d_name, "." ) == 0 ) || ( strcmp( entry->d_name, ".." ) ) == 0 )
			{
				continue;
			}
			if((*dirPaths) == NULL)
			{
				*dirPaths = malloc(sizeof(fileList));
				(*dirPaths)->path = malloc(sizeof(filePath));
				(*dirPaths)->path->string = malloc(strlen(path->string) + 1);
				strcpy( (*dirPaths)->path->string, path->string  );
				(*dirPaths)->next = NULL;
				indexFiles( path, filePaths, dirPaths );
				return 0;
			}
			else
			{
				//make string, then recreate it from stack to heap
				/// [MALLOC]
				char newString[ 1024 ];
				int len = snprintf ( newString, sizeof(newString) - 1, "%s/%s", path->string, entry->d_name );
				newString[len] = '\0';
				
				fileList *newFile;
				newFile = (*dirPaths);
				
				while(newFile->next)
				{
					newFile = newFile->next;
				}
				(newFile->next) = malloc(sizeof(fileList));
				
				newFile->next->path = malloc(sizeof(filePath));
				newFile->next->path->string = malloc(strlen(newString) + 1);
				strcpy( newFile->next->path->string, newString  );
				newFile->next->next = NULL;
				
				/// [MALLOC]
				filePathPtr newPath = stringStructCreate( newString );

				indexFiles( newPath, filePaths, dirPaths );		
			}
		}
		//file
		else
		{
			//ignore temp files
			if( ( entry->d_name[ strlen( entry->d_name ) - 1 ] != '~' ) )
			{
				/// [MALLOC]
				char *newString = ( char* )malloc( strlen( path->string ) + strlen( entry->d_name ) + 2 );
					strcpy( newString, path->string );
					strcat( newString, "/" );
					strcat( newString, entry->d_name );
					newString[ strlen( newString ) ] = '\0';
				if((*filePaths) == NULL)
				{
					//*filePaths = fileListCreate(newString);
					*filePaths = malloc(sizeof(fileList));
					(*filePaths)->path = malloc(sizeof(filePath));
					(*filePaths)->path->string = malloc(strlen(newString) + 1 );
					strcpy( (*filePaths)->path->string, newString );
					(*filePaths)->next = NULL;
				}
				else
				{
					fileList *newFile;
					newFile = (*filePaths);
					
					while(newFile->next)
					{
						newFile = newFile->next;
					}					
					
					newFile->next = malloc(sizeof(fileList));
					newFile->next->path = malloc(sizeof(filePath));
					newFile->next->path->string = malloc(strlen(newString) + 1 );
					strcpy( newFile->next->path->string, newString );
					newFile->next->next = NULL;
				}
					
					//printf("\n%s", (*filePaths)->path->string);
					
				FREE( newString );	//
			}
		}
	}
	while ( ( entry = readdir( dir ) ) );

	closedir( dir );
	
	return 0;
}



int readDir(char* file, container **head)
{	
	FILE *fp;
	long fileSize = 0;
	
	fp = fopen(file, "r");
	
	if(!fp)
	{
		fprintf(stderr, "Could not open file:\n %s.\n\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
		
	fseek(fp, 0, SEEK_END);
	fileSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	
	if(fileSize == 0)
	{
		return;
	}
	
	//char *contentString = (char*)malloc(fileSize + 1);
	char *contentString = calloc(fileSize, 1);
	fread(contentString, fileSize, 1, fp);
		stringNonAlphaToSpace(contentString);
		stringLowerCase(contentString);
	char *tempToken;
	tempToken = strtok(contentString, " ");
	
	while(tempToken != NULL)
	{

		if ((*head) == NULL)
		{
			*head = malloc(sizeof(container));
			(*head)->token = malloc( strlen(tempToken) + 1 );
					strcpy( (*head)->token, tempToken );
			(*head)->path = malloc ( strlen( file ) + 1);
				strcpy((*head)->path, file);
				(*head)->next = NULL;			
		}
		else
		{
			container *newWordList;
			newWordList = (*head);
			
			while(newWordList->next)
			{
				newWordList = newWordList->next;
			}
			(newWordList->next) = malloc(sizeof(wordList));
			newWordList->next->token = malloc(strlen(  tempToken ) + 1);
				strcpy(newWordList->next->token, tempToken);
			newWordList->next->path = malloc(strlen ( file ) + 1);
				strcpy(newWordList->next->path, file);
			newWordList->next->next = NULL;
		}
		printf("\n%s", tempToken);
		tempToken = strtok(NULL, " ");
	}
	
}
