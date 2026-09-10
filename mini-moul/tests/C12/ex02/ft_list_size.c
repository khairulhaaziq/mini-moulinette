// ALLOWED_FUNCTIONS: 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../utils/ft_list.h"
#include "../../../../ex02/ft_list_size.c"
#include "../../../utils/constants.h"

static t_list *moul_new_node(void *data)
{
	t_list *node;

	node = malloc(sizeof(t_list));
	node->data = data;
	node->next = NULL;
	return (node);
}

static t_list *moul_build_list(int n)
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
		*data = i;
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

typedef struct s_test
{
	char *desc;
	int build;
	int expected;
} t_test;

int run_tests(t_test *tests, int count);

int main(void)
{
	t_test tests[] = {
		{.desc = "ft_list_size on an empty list", .build = 0, .expected = 0},
		{.desc = "ft_list_size on a 1-element list", .build = 1, .expected = 1},
		{.desc = "ft_list_size on a 5-element list", .build = 5, .expected = 5},
	};
	int count = sizeof(tests) / sizeof(tests[0]);

	return (run_tests(tests, count));
}

int run_tests(t_test *tests, int count)
{
	int i;
	int error = 0;

	for (i = 0; i < count; i++)
	{
		t_list *list = moul_build_list(tests[i].build);
		int result = ft_list_size(list);

		if (result != tests[i].expected)
		{
			printf("    " RED "[%d] %s Expected %d, got %d\n" DEFAULT, i + 1, tests[i].desc, tests[i].expected, result);
			error -= 1;
		}
		else
			printf("  " GREEN CHECKMARK GREY " [%d] %s Expected %d, got %d\n" DEFAULT, i + 1, tests[i].desc, tests[i].expected, result);
		moul_free_list(list);
	}
	return (error);
}
