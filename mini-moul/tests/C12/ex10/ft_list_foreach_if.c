// ALLOWED_FUNCTIONS: 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../utils/ft_list.h"
#include "../../../../ex10/ft_list_foreach_if.c"
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
	int values[] = {1, 2, 1, 3, 1};
	int *data;
	int i;
	int ok;
	int ref = 1;

	head = NULL;
	tail = NULL;
	i = 0;
	while (i < 5)
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
	ft_list_foreach_if(head, &moul_record, &ref, &moul_cmp_int);

	ok = (g_call_count == 3 && g_calls[0] == 1 && g_calls[1] == 1 && g_calls[2] == 1);
	if (!ok)
		printf("    " RED "[1] ft_list_foreach_if() did not apply f only to matching elements, in order (got %d calls)\n" DEFAULT, g_call_count);
	else
		printf("  " GREEN CHECKMARK GREY " [1] ft_list_foreach_if() applied f only to matching elements, in order\n" DEFAULT);
	moul_free_list(head);
	return (ok ? 0 : -1);
}
