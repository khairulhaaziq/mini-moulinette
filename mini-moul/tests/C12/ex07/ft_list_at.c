// ALLOWED_FUNCTIONS: 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../utils/ft_list.h"
#include "../../../../ex07/ft_list_at.c"
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
	int i;
	int ok;
	t_list *result;

	i = 0;
	while (i < 4)
	{
		int *data = malloc(sizeof(int));
		*data = i;
		nodes[i] = moul_new_node(data);
		if (i > 0)
			nodes[i - 1]->next = nodes[i];
		i++;
	}

	ok = 1;
	if (ft_list_at(nodes[0], 0) != nodes[0])
		ok = 0;
	if (ft_list_at(nodes[0], 2) != nodes[2])
		ok = 0;
	if (ft_list_at(nodes[0], 3) != nodes[3])
		ok = 0;
	result = ft_list_at(nodes[0], 4);
	if (result != NULL)
		ok = 0;
	result = ft_list_at(nodes[0], 100);
	if (result != NULL)
		ok = 0;

	if (!ok)
		printf("    " RED "[1] ft_list_at() did not return the correct element, or NULL out of range\n" DEFAULT);
	else
		printf("  " GREEN CHECKMARK GREY " [1] ft_list_at() returned the correct element, and NULL out of range\n" DEFAULT);
	moul_free_list(nodes[0]);
	return (ok ? 0 : -1);
}
