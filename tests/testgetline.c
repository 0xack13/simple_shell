#include "shell.h"

int main()
{
        char *input;
	int i;

	while((i = _getline(&input, STDIN_FILENO)) != -1)
	{
		printf("\n[input] %s\n", input);
		printf("[i] %d\n", i);
	}
	return (0);
}

/**
* run of _getline is as expected :)
**/
