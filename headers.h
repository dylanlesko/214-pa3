#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include "indexer.h"
#include "inverted-list.h"
#include "format.h"
#include <unistd.h>
#include "output.h"


typedef enum { false, true} boolean;

#define FREE(ptr) 		\
	do{ 				\
		free((ptr));	\
		(ptr)=NULL;		\
	}while(0) 


//bluesock.org/~willg/dev/ansi.html
#define RESET_FORMAT "\e[m"
#define MAKE_GREEN "\e[32m"
#define MAKE_RED "\e[31m"
#define MAKE_BLACK "\e[30m"
#define MAKE_YELLOW "\e[33m"
#define MAKE_BLUE "\e[34m"
#define MAKE_PURPLE "\e[35m"
#define MAKE_CYAN "\e[36m"
#define MAKE_WHITE "\e[37m"
#define MAKE_UNDERLINE "\e[4m"

//FILE *tempFile(void)
