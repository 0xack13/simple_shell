#include "shell.h"

void add_mem(void **p, save_mem **head)
{
	save_mem *newnode;

	/*create node */
	newnode = malloc(sizeof(save_mem));
	newnode->loc = *p;

	if (!*head)
	{
		newnode->next = NULL;
		*head = newnode;
	}
	else
	{
		/* prepend to LL, FIFO */
		newnode->next = *head;
		*head = newnode;
	}
}

void remove_mem(void **p, save_mem **head)
{
	save_mem *tmp, *hold;

	tmp = *head;
	if (p == NULL)
	{
		/* remove and free all nodes */
		while (tmp)
		{
			hold = tmp;
			tmp = tmp->next;
			free(hold->loc);
			free(hold);
		}
		*head = NULL;
	}

	//remove only *p
	hold = tmp;
	while (tmp)
	{
		if (tmp->loc == p)
		{
			if (hold == tmp)
				*head = tmp->next;
			else
				hold->next = tmp->next;

			free(tmp->loc);
			free(tmp);
			break;
		}
		hold = tmp;
		tmp = tmp->next;
	}
}

void _ref_mem(void *p, char *action)
{
	static save_mem *head = NULL;
	save_mem *newnode;

	if (_strcmp(action, "create") == 0)
		add_mem(&p, &head);
	else if (_strcmp(action, "remove") == 0)
		remove_mem(&p, &head);
}

void *_malloc(unsigned int size)
{
	void *p;

	p = malloc(size);
	printf("address in _malloc p, &p: %p, %p\n", p, &p);
	if (p == NULL)
		return (NULL);

	_ref_mem(p, "create");

	return (p);
}

void _free(void *ptr)
{
	_ref_mem(ptr, "remove");
}
/*
void printLL(save_mem **head)
{
	save_mem *tmp;
	int i;

	printf("Start printLL\n");

	i = 1;
	tmp = *head;
	while (tmp != NULL)
	{
		printf("%d. pointer: %p\n", i, tmp);
		printf("\t%p\n", tmp->loc);
		tmp = tmp->next;
		i++;
	}

	printf("end of printLL\n//////////\n\n");
	}*/
/*
int main(void)
{
	static save_mem *head = NULL;


	char *a;
	int i, size;

	size = 2;

	a = _malloc(10, &head);
	a[0] = 'a';
	a[1] = 'b';
	printf("address in main: %p\n", a);
	printf("-------\n%s\n------\n", a);
	printLL(&head);
	_free(a, &head);
	printf("---\n");
	printLL(&head);

	for (i = 0; i < 20; i++)
	{
		a = _malloc(size, &head);
	}

	printf("in main, head: %p\n", head);
	printLL(&head);

	_free(NULL, &head);
	printLL(&head);

	return (0);
}
*/
