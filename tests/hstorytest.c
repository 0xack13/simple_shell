#include "shell.h"

int main()
{
	char *fileaddrss = _getenv("HOME");
	printf("[home] %s\n", fileaddrss);
	char *file = _strcat(fileaddrss, ".simple_shell_history", '/');
	printf("[file] %s\n", file);
	static hstory *head = NULL;
	int hstryCount = readFromFile("/home/vagrant/simple_shell/.simple_shell_history", &head);
	printf("[count] %d\n", hstryCount);
	addHistory(&head, "lssl\n");
	addHistory(&head, "pwdd\n");
	addHistory(&head, "whatsup\n");
        addHistory(&head, "man\n");
	writeHstorytofile("/home/vagrant/simple_shell/.simple_shell_history", &head);
	return (0);
}
