// ALLOWED_FUNCTIONS: free
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../utils/ft_list.h"
#include "../../../../ex06/ft_list_clear.c"
#include "../../../utils/constants.h"

static void *g_freed[64];
static int g_freed_count;

static void moul_free_track(void *p)
{
	if (g_freed_count < 64)
		g_freed[g_freed_count] = p;
	g_freed_count++;
	free(p);
}

static t_list *moul_new_node(void *data)
{
	t_list *node;

	node = malloc(sizeof(t_list));
	node->data = data;
	node->next = NULL;
	return (node);
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
	t_list *n1;
	t_list *n2;
	t_list *n3;
	void *data[3];
	int i;
	int j;
	int ok;
	int found;

	data[0] = malloc(sizeof(int));
	data[1] = malloc(sizeof(int));
	data[2] = malloc(sizeof(int));
	n1 = moul_new_node(data[0]);
	n2 = moul_new_node(data[1]);
	n3 = moul_new_node(data[2]);
	n1->next = n2;
	n2->next = n3;

	g_freed_count = 0;
	ft_list_clear(n1, &moul_free_track);

	ok = (g_freed_count == 3);
	i = 0;
	while (ok && i < 3)
	{
		found = 0;
		j = 0;
		while (j < g_freed_count)
		{
			if (g_freed[j] == data[i])
				found = 1;
			j++;
		}
		if (!found)
			ok = 0;
		i++;
	}
	if (!ok)
		printf("    " RED "[1] ft_list_clear() did not free every element's data exactly once (freed %d)\n" DEFAULT, g_freed_count);
	else
		printf("  " GREEN CHECKMARK GREY " [1] ft_list_clear() freed every element's data exactly once\n" DEFAULT);
	return (ok ? 0 : -1);
}
