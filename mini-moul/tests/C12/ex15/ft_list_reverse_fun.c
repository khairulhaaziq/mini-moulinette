// ALLOWED_FUNCTIONS: 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../utils/ft_list.h"
#include "../../../../ex15/ft_list_reverse_fun.c"
#include "../../../utils/constants.h"

static t_list *moul_new_node(void *data)
{
	t_list *node;

	node = malloc(sizeof(t_list));
	node->data = data;
	node->next = NULL;
	return (node);
}

static t_list *moul_build_list(int *values, int n)
{
	t_list *head;
	t_list *tail;
	t_list *node;
	int i;
	int *data;

	head = NULL;
	tail = NULL;
	i = 0;
	while (i < n)
	{
		data = malloc(sizeof(int));
		*data = values[i];
		node = moul_new_node(data);
		if (!head)
			head = node;
		else
			tail->next = node;
		tail = node;
		i++;
	}
	return (head);
}

static int moul_list_to_array(t_list *lst, int *out, int max)
{
	int n;

	n = 0;
	while (lst && n < max)
	{
		out[n] = *(int *)lst->data;
		n++;
		lst = lst->next;
	}
	return (n);
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
	/*
	 * The subject prototypes this as void ft_list_reverse_fun(t_list *begin_list),
	 * taking the head by value (unlike ex08's ft_list_reverse, which takes a
	 * t_list **). Since the caller's head pointer can't be redirected, the
	 * head node itself must stay the same object: only the data must end up
	 * reversed, e.g. by swapping data between symmetric positions.
	 */
	int values[] = {1, 2, 3, 4, 5};
	t_list *list = moul_build_list(values, 5);
	t_list *original_head = list;
	int result[8];
	int n;
	int ok;

	ft_list_reverse_fun(list);
	n = moul_list_to_array(list, result, 8);
	ok = (list == original_head && n == 5 && result[0] == 5 && result[1] == 4 && result[2] == 3 && result[3] == 2 && result[4] == 1);
	if (!ok)
		printf("    " RED "[1] ft_list_reverse_fun() did not reverse the list's element order correctly\n" DEFAULT);
	else
		printf("  " GREEN CHECKMARK GREY " [1] ft_list_reverse_fun() reversed the list's element order correctly\n" DEFAULT);
	moul_free_list(list);
	return (ok ? 0 : -1);
}
