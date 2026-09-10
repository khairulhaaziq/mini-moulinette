// ALLOWED_FUNCTIONS: free
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../utils/ft_list.h"
#include "../../../../ex12/ft_list_remove_if.c"
#include "../../../utils/constants.h"

static t_list *moul_new_node(void *data)
{
	t_list *node;

	node = malloc(sizeof(t_list));
	node->data = data;
	node->next = NULL;
	return (node);
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

static int g_freed_count;

static void moul_free_track(void *p)
{
	g_freed_count++;
	free(p);
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
	t_list *head;
	t_list *tail;
	t_list *node;
	int values[] = {1, 2, 1, 3, 1, 4};
	int *data;
	int i;
	int ok;
	int ref = 1;
	int result[8];
	int n;

	head = NULL;
	tail = NULL;
	i = 0;
	while (i < 6)
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

	g_freed_count = 0;
	ft_list_remove_if(&head, &ref, &moul_cmp_int, &moul_free_track);

	n = moul_list_to_array(head, result, 8);
	ok = (n == 3 && result[0] == 2 && result[1] == 3 && result[2] == 4 && g_freed_count == 3);
	if (!ok)
		printf("    " RED "[1] ft_list_remove_if() did not remove and free exactly the matching elements (got %d remaining, %d freed)\n" DEFAULT, n, g_freed_count);
	else
		printf("  " GREEN CHECKMARK GREY " [1] ft_list_remove_if() removed and freed exactly the matching elements\n" DEFAULT);
	moul_free_list(head);
	return (ok ? 0 : -1);
}
