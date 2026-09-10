// ALLOWED_FUNCTIONS: 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../utils/ft_list.h"
#include "../../../../ex13/ft_list_merge.c"
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
	int v1[] = {1, 2};
	int v2[] = {3, 4};
	t_list *list1 = moul_build_list(v1, 2);
	t_list *list2 = moul_build_list(v2, 2);
	t_list *list2_head = list2;
	int result[8];
	int n;
	int ok;

	ft_list_merge(&list1, list2);
	n = moul_list_to_array(list1, result, 8);
	ok = (n == 4 && result[0] == 1 && result[1] == 2 && result[2] == 3 && result[3] == 4);
	/* element creation is forbidden, so begin2's original nodes must be reused as-is */
	if (ok)
	{
		t_list *cursor = list1;

		while (cursor && cursor->data != list2_head->data)
			cursor = cursor->next;
		if (cursor != list2_head)
			ok = 0;
	}
	if (!ok)
		printf("    " RED "[1] ft_list_merge() did not append list2's original nodes to the end of list1\n" DEFAULT);
	else
		printf("  " GREEN CHECKMARK GREY " [1] ft_list_merge() appended list2's original nodes to the end of list1\n" DEFAULT);
	moul_free_list(list1);
	return (ok ? 0 : -1);
}
