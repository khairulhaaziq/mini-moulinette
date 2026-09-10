// ALLOWED_FUNCTIONS: ft_create_elem
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../utils/ft_list.h"
#include "../../../../ex16/ft_sorted_list_insert.c"
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
int test2(void);
int test3(void);

int main(void)
{
	int error = 0;

	if (test1() != 0)
		error -= 1;
	if (test2() != 0)
		error -= 1;
	if (test3() != 0)
		error -= 1;
	return (error);
}

static int moul_check(t_list *list, int *expected, int n, char *desc, int idx)
{
	int result[16];
	int got = moul_list_to_array(list, result, 16);
	int i;
	int ok = (got == n);

	for (i = 0; ok && i < n; i++)
	{
		if (result[i] != expected[i])
			ok = 0;
	}
	if (!ok)
		printf("    " RED "[%d] %s\n" DEFAULT, idx, desc);
	else
		printf("  " GREEN CHECKMARK GREY " [%d] %s\n" DEFAULT, idx, desc);
	return (ok);
}

int test1(void)
{
	int values[] = {1, 3, 5};
	t_list *list = moul_build_list(values, 3);
	int *new_data = malloc(sizeof(int));
	int expected[] = {1, 3, 4, 5};
	int ok;

	*new_data = 4;
	ft_sorted_list_insert(&list, new_data, &moul_cmp_int);
	ok = moul_check(list, expected, 4, "ft_sorted_list_insert() inserted into the middle correctly", 1);
	moul_free_list(list);
	return (ok ? 0 : -1);
}

int test2(void)
{
	int values[] = {1, 3, 5};
	t_list *list = moul_build_list(values, 3);
	int *new_data = malloc(sizeof(int));
	int expected[] = {0, 1, 3, 5};
	int ok;

	*new_data = 0;
	ft_sorted_list_insert(&list, new_data, &moul_cmp_int);
	ok = moul_check(list, expected, 4, "ft_sorted_list_insert() inserted at the head correctly", 2);
	moul_free_list(list);
	return (ok ? 0 : -1);
}

int test3(void)
{
	t_list *list = NULL;
	int *new_data = malloc(sizeof(int));
	int expected[] = {42};
	int ok;

	*new_data = 42;
	ft_sorted_list_insert(&list, new_data, &moul_cmp_int);
	ok = moul_check(list, expected, 1, "ft_sorted_list_insert() inserted into an empty list correctly", 3);
	moul_free_list(list);
	return (ok ? 0 : -1);
}
