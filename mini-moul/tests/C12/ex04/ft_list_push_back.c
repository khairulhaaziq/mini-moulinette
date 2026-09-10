// ALLOWED_FUNCTIONS: ft_create_elem
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../utils/ft_list.h"
#include "../../../../ex04/ft_list_push_back.c"
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
int test2(void);

int main(void)
{
	int error = 0;

	if (test1() != 0)
		error -= 1;
	if (test2() != 0)
		error -= 1;
	return (error);
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
		ft_list_push_back(&list, data);
		i++;
	}
	n = moul_list_to_array(list, result, 8);
	ok = (n == 3 && result[0] == 1 && result[1] == 2 && result[2] == 3);
	if (!ok)
		printf("    " RED "[1] ft_list_push_back() did not append elements in order (got %d elements)\n" DEFAULT, n);
	else
		printf("  " GREEN CHECKMARK GREY " [1] ft_list_push_back() appended elements in order\n" DEFAULT);
	moul_free_list(list);
	return (ok ? 0 : -1);
}

int test2(void)
{
	t_list *list;
	int value = 42;
	int result[8];
	int n;
	int ok;

	list = NULL;
	ft_list_push_back(&list, &value);
	n = moul_list_to_array(list, result, 8);
	ok = (n == 1 && result[0] == 42 && list != NULL);
	if (!ok)
		printf("    " RED "[2] ft_list_push_back() on an empty list did not create the first element\n" DEFAULT);
	else
		printf("  " GREEN CHECKMARK GREY " [2] ft_list_push_back() on an empty list created the first element\n" DEFAULT);
	if (list)
		free(list);
	return (ok ? 0 : -1);
}
