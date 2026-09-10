// ALLOWED_FUNCTIONS: 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../utils/ft_list.h"
#include "../../../../ex17/ft_sorted_list_merge.c"
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
	int v1[] = {1, 3, 5, 7};
	int v2[] = {2, 4, 6};
	t_list *list1 = moul_build_list(v1, 4);
	t_list *list2 = moul_build_list(v2, 3);
	int expected[] = {1, 2, 3, 4, 5, 6, 7};
	int result[16];
	int n;
	int i;
	int ok;

	ft_sorted_list_merge(&list1, list2, &moul_cmp_int);
	n = moul_list_to_array(list1, result, 16);
	ok = (n == 7);
	for (i = 0; ok && i < 7; i++)
	{
		if (result[i] != expected[i])
			ok = 0;
	}
	if (!ok)
		printf("    " RED "[1] ft_sorted_list_merge() did not merge the two sorted lists correctly\n" DEFAULT);
	else
		printf("  " GREEN CHECKMARK GREY " [1] ft_sorted_list_merge() merged the two sorted lists correctly\n" DEFAULT);
	moul_free_list(list1);
	return (ok ? 0 : -1);
}
