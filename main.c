#include "headers.h"

int main ( int argc, char *argv[ ] ) 
{
	
	system("clear");
	if(argc != 3)
	{
		printf(	"\nIncorrect Number of Arguments.\n./indexer <outputfile> <dir>\n\n");
		return 1;
	}
	
	///	[MALLOC]
	filePathPtr inputPath = stringStructCreate( argv[ 2 ] );
	//filePath *outputPath = stringStructCreate("1");
	///	[MALLOC]
	filePathPtr outputPath = stringStructCreate( argv[ 1 ] );
	//filePath *inputPath = stringStructCreate("Untitled Folder");
	
	///	[MALLOC]
	fileListPtr filePaths = NULL;
	///	[MALLOC]
	fileListPtr dirPaths = NULL;
	
	//gather all the files in the directory
	indexFiles ( inputPath, &filePaths, &dirPaths );
	
	//read the files, and create a list of the tokens
	container *mergedList = NULL;
	fileList *fileIter = filePaths;
	while(fileIter != NULL)
	{
		readDir(fileIter->path->string,  &mergedList);
		fileIter = fileIter->next;
	}
	
	//add the tokens to a list
	container *listIter = mergedList;
	ILNode *index = NULL;
	while( listIter != NULL)
	{
		buildList(&index, listIter);
		listIter = listIter->next;
	}
	//ILPrint(index);
	
	mergeSort(&index);
	
	ILNode *nodeIter = index;
	while(nodeIter != NULL)
	{
		mergeSortRecords(&(nodeIter->pathData));
		nodeIter = nodeIter->next;
	}
	
	ILPrint(index);

	output(outputPath->string, index);
	
	printf("\n\n");
	return 0;	
}
