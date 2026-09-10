// ALLOWED_FUNCTIONS: ft_create_elem
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../utils/ft_list.h"
#include "../../../../ex01/ft_list_push_front.c"
#include "../../../utils/constants.h"

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
	t_list *list;
	int values[] = {1, 2, 3};
	int *data;
	int i;
	int result[8];
	int n;
	int ok;

	list = NULL;
	i = 0;
	while (i < 3)
	{
		data = malloc(sizeof(int));
		*data = values[i];
		ft_list_push_front(&list, data);
		i++;
	}
	n = moul_list_to_array(list, result, 8);
	ok = (n == 3 && result[0] == 3 && result[1] == 2 && result[2] == 1);
	if (!ok)
	{
		printf("    " RED "[1] ft_list_push_front() did not build the expected list (got %d elements)\n" DEFAULT, n);
	}
	else
		printf("  " GREEN CHECKMARK GREY " [1] ft_list_push_front() built the expected list, front to back\n" DEFAULT);
	moul_free_list(list);
	return (ok ? 0 : -1);
}
