// ALLOWED_FUNCTIONS: 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../utils/ft_list.h"
#include "../../../../ex11/ft_list_find.c"
#include "../../../utils/constants.h"

static t_list *moul_new_node(void *data)
{
	t_list *node;

	node = malloc(sizeof(t_list));
	node->data = data;
	node->next = NULL;
	return (node);
}

static void moul_free_list(t_list *lst)
{
	t_list *next;

	while (lst)
	{
		next = lst->next;
		free(lst->data);
		free(lst);
		lst = next;
	}
}

static int moul_cmp_int(void *a, void *b)
{
	return (*(int *)a - *(int *)b);
}

int test1(void);

int main(void)
{
	if (test1() != 0)
		return (-1);
	return (0);
}

int test1(void)
{
	t_list *nodes[4];
	int values[] = {10, 20, 30, 40};
	int i;
	int ok;
	t_list *result;
	int not_found = 99;

	i = 0;
	while (i < 4)
	{
		int *data = malloc(sizeof(int));
		*data = values[i];
		nodes[i] = moul_new_node(data);
		if (i > 0)
			nodes[i - 1]->next = nodes[i];
		i++;
	}

	ok = 1;
	result = ft_list_find(nodes[0], &values[2], &moul_cmp_int);
	if (result != nodes[2])
		ok = 0;
	result = ft_list_find(nodes[0], &not_found, &moul_cmp_int);
	if (result != NULL)
		ok = 0;

	if (!ok)
		printf("    " RED "[1] ft_list_find() did not return the correct element, or NULL when not found\n" DEFAULT);
	else
		printf("  " GREEN CHECKMARK GREY " [1] ft_list_find() returned the correct element, and NULL when not found\n" DEFAULT);
	moul_free_list(nodes[0]);
	return (ok ? 0 : -1);
}
