// ALLOWED_FUNCTIONS: 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../utils/ft_list.h"
#include "../../../../ex03/ft_list_last.c"
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
int test2(void);

int main(void)
{
	int error = 0;

	if (test1() != 0)
		error -= 1;
	if (test2() != 0)
		error -= 1;
	return (error);
}

int test1(void)
{
	t_list *n1 = moul_new_node(malloc(sizeof(int)));
	t_list *n2 = moul_new_node(malloc(sizeof(int)));
	t_list *n3 = moul_new_node(malloc(sizeof(int)));
	t_list *result;
	int ok;

	n1->next = n2;
	n2->next = n3;
	result = ft_list_last(n1);
	ok = (result == n3);
	if (!ok)
		printf("    " RED "[1] ft_list_last() did not return the address of the last element\n" DEFAULT);
	else
		printf("  " GREEN CHECKMARK GREY " [1] ft_list_last() returned the address of the last element\n" DEFAULT);
	moul_free_list(n1);
	return (ok ? 0 : -1);
}

int test2(void)
{
	t_list *n1 = moul_new_node(malloc(sizeof(int)));
	t_list *result;
	int ok;

	result = ft_list_last(n1);
	ok = (result == n1);
	if (!ok)
		printf("    " RED "[2] ft_list_last() on a single-element list did not return that element\n" DEFAULT);
	else
		printf("  " GREEN CHECKMARK GREY " [2] ft_list_last() on a single-element list returned that element\n" DEFAULT);
	moul_free_list(n1);
	return (ok ? 0 : -1);
}
