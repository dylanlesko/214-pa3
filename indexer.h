#ifndef INDEXER_H
#define INDEXER_H
#include "inverted-list.h"

int 	readFiles		( fileListPtr	filePaths, 	tokenListPtr 	fileTokensList									);
int 	indexFiles		( filePathPtr	path, 		fileList		**filePaths,		fileList		**dirPaths		);


#endif
