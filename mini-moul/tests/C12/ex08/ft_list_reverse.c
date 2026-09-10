// ALLOWED_FUNCTIONS: 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../utils/ft_list.h"
#include "../../../../ex08/ft_list_reverse.c"
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
	int values[] = {1, 2, 3, 4};
	int *data;
	int i;
	int result[8];
	int n;
	int ok;

	head = NULL;
	tail = NULL;
	i = 0;
	while (i < 4)
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

	ft_list_reverse(&head);
	n = moul_list_to_array(head, result, 8);
	ok = (n == 4 && result[0] == 4 && result[1] == 3 && result[2] == 2 && result[3] == 1);
	if (!ok)
		printf("    " RED "[1] ft_list_reverse() did not reverse the list correctly (got %d elements)\n" DEFAULT, n);
	else
		printf("  " GREEN CHECKMARK GREY " [1] ft_list_reverse() reversed the list correctly\n" DEFAULT);
	moul_free_list(head);
	return (ok ? 0 : -1);
}
