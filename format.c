#include "headers.h" 

void stringNonAlphaToSpace(char *input){
	unsigned long i = 0;
	unsigned long j = 0;
	char c;

	while ( (c = input[i++]) != '\0')
	{
		if(isalnum(c))
		{
			input[j++] = tolower(c);
		}
		else
		{
			input[j++] = ' ';
		}
	}
	//input[j-1] = '\0';
	//input[j] = '\0';
}

void stringLowerCase(char *input)
{
	int i = 0;
	for(i = 0; input[i]; i++)
	{
		input[i] = tolower(input[i]);
	}
}
