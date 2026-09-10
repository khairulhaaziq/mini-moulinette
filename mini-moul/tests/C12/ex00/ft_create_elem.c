// ALLOWED_FUNCTIONS: malloc
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../utils/ft_list.h"
#include "../../../../ex00/ft_create_elem.c"
#include "../../../utils/constants.h"

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
	int value = 42;
	t_list *node = ft_create_elem(&value);
	int ok = 1;

	if (!node)
		ok = 0;
	else
	{
		if (node->data != &value)
			ok = 0;
		if (node->next != NULL)
			ok = 0;
	}
	if (!ok)
		printf("    " RED "[1] ft_create_elem() did not build a valid node (data and next set correctly)\n" DEFAULT);
	else
		printf("  " GREEN CHECKMARK GREY " [1] ft_create_elem() built a valid node with data and next set correctly\n" DEFAULT);
	if (node)
		free(node);
	return (ok ? 0 : -1);
}

int test2(void)
{
	t_list *node = ft_create_elem(NULL);
	int ok = 1;

	if (!node)
		ok = 0;
	else
	{
		if (node->data != NULL)
			ok = 0;
		if (node->next != NULL)
			ok = 0;
	}
	if (!ok)
		printf("    " RED "[2] ft_create_elem(NULL) did not build a valid node\n" DEFAULT);
	else
		printf("  " GREEN CHECKMARK GREY " [2] ft_create_elem(NULL) built a valid node\n" DEFAULT);
	if (node)
		free(node);
	return (ok ? 0 : -1);
}
