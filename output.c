#include "headers.h"

int 	output	( char*	file,	ILNode 	*head	)
{
	printf("\n%s", file);
	if( access (file, F_OK) != -1)
	{
		printf("\nFile Already Exists. Overwrite? (Y/N)?: \n");
		
		if(tolower(getchar()) == 'y')
		{
			remove(file);
		}
		else
		{
			printf("\nProgram Terminated.\n");
			return 1;
		}
		
	}
	
	FILE *fp;
	fp = fopen(file, "ab+");
	
	ILNode *tokenIter;
	fileNode *pathIter;
	tokenIter = head;
	
	while(tokenIter != NULL)
	{
		fprintf(fp, "<list>\n");
		fprintf(fp, "%s\n", tokenIter->token);
		
		pathIter = tokenIter->pathData;
		
		while(pathIter != NULL)
		{
			fprintf(fp, "%s", pathIter->path);
			fprintf(fp, "\t\t\t%d\n", pathIter->freq);
			pathIter = pathIter->next;
		}
		fprintf(fp, "</list>\n");
		tokenIter = tokenIter->next;
	}
	fclose(fp);
	
}
