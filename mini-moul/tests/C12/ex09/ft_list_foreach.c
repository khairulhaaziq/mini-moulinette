// ALLOWED_FUNCTIONS: 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../utils/ft_list.h"
#include "../../../../ex09/ft_list_foreach.c"
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

static int g_calls[64];
static int g_call_count;

static void moul_record(void *data)
{
	if (g_call_count < 64)
		g_calls[g_call_count] = *(int *)data;
	g_call_count++;
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
	int values[] = {5, 10, 15};
	int *data;
	int i;
	int ok;

	head = NULL;
	tail = NULL;
	i = 0;
	while (i < 3)
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

	g_call_count = 0;
	ft_list_foreach(head, &moul_record);

	ok = (g_call_count == 3 && g_calls[0] == 5 && g_calls[1] == 10 && g_calls[2] == 15);
	if (!ok)
		printf("    " RED "[1] ft_list_foreach() did not apply f to every element, in order\n" DEFAULT);
	else
		printf("  " GREEN CHECKMARK GREY " [1] ft_list_foreach() applied f to every element, in order\n" DEFAULT);
	moul_free_list(head);
	return (ok ? 0 : -1);
}
