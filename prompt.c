#include "shell.h"

char *read_input()
{
	char *line;
	ssize_t bufr;

	line = NULL;
	bufr = 0;
	if (getline(&line, &bufr, stdin) == -1)
		return NULL;
	return line;
}

char **split_input(char *input)
{
	int i;
	char **tokens, *tokn;

	tokens = malloc(1024 * sizeof(char *));
	if (tokens == NULL)
	{
		dprintf(STDERR_FILENO, "Allocation Error\n");
		exit (0);
	}
	tokn = strtok(input, " \n");
	i = 0;
	while (tokn != NULL)
	{
		tokens[i] = tokn;
		i++;
		tokn = strtok(NULL, " \n");
	}
	tokens[i] = NULL;
	return (tokens);
}

char *_strcat(const char *str1, const char *str2, char formatter)
{
	char *new;
	int i, j;

	new = malloc(sizeof(char) * (_strlen(str1) + _strlen(str2) + 2));
	if (new == NULL)
		return (NULL);

	for (i = 0; str1[i] != '\0'; i++)
		new[i] = str1[i];

	new[i] = formatter;
	i++;

	for (j = 0; str2[j] != '\0'; j++)
		new[i] = str2[j];

	new[i] = '\0';
	return (new);
}

void excute(char **tokens)
{
	pid_t pid, wpid;
	int status, i;
	char *path, *tokn, *concat;

	pid = fork();
	if (pid == -1)
	{
		dprintf(STDERR_FILENO, "Forking Error\n");
		exit(0);
	}
	if (pid == 0)
	{
		if (tokens[0][0] != '/')
		{
			path = _getenv("PATH");
			tokn = strtok(path, ":");
			while (tokn)
			{
				concat = _strcat(tokn, tokens[0], '/');
				if (concat)
				{
					if (execve(concat, tokens, NULL) == -1)
						dprintf(STDERR_FILENO, "No such file or directory");
				}
				tokn = strtok(NULL, ":");
			}
		}
		if (tokens[0][0] == '/')
		{
			if (execve(tokens[0], tokens, NULL) == -1)
				dprintf(STDERR_FILENO, "No such file or directory\n");
		}
	}
	else
		wait(&status);
}

void prompt(void)
{
 	char *input, **tokens;

	printf("$ ");
	do
	{
		input = read_input();
		if (input != NULL)
			printf("$ ");
		tokens = split_input(input);
	       	excute(tokens);
		free(input);
		free(tokens);
	}
	while (input != NULL);
}
int main(int argc, char **argv)
{
	prompt();
	return (0);
}
