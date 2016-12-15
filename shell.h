#ifndef SHELL
#define SHELL

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <ctype.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef struct strLL
{
	char *str;
	struct strLL *next;
} strLL;

typedef struct in_built
{
	char *s;
	void (*func) (char **);
} in_built;

int checkEnv(char *name);
int _strlen(char *str);
char *_strcpy(char *strng, int i);
int _strcmp(char *s1, char *s2);
char **deepDupe(char **args);
char *_strcat(char *str1, char *str2, char formatter);
void chng_dr(char **str);
void ext(char **str);
void hlp(char **str);
void hstry(char **str);
void printEnv(char **str);
char *_getenv(char *name);
void _setenv(char **str);
void _unsetenv(char **str);
char **split_input(char *input);
int find_builtins(char **tokens);
void check_path(char **tokens);
void excute(char **tokens);
void prompt(void);



#endif
