// ALLOWED_FUNCTIONS: ft_create_elem
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../utils/ft_list.h"
#include "../../../../ex05/ft_list_push_strs.c"
#include "../../../utils/constants.h"

static void moul_free_list(t_list *lst)
{
	t_list *next;

	while (lst)
	{
		next = lst->next;
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
	char *strs[] = {"one", "two", "three"};
	t_list *list;
	t_list *cursor;
	int ok;
	int i;

	/* the subject states the first element of strs ends up at the end of
	 * the list, and the address of the first (head) link is returned */
	list = ft_list_push_strs(3, strs);
	ok = 1;
	cursor = list;
	i = 2;
	while (cursor && i >= 0)
	{
		if (cursor->data != (void *)strs[i])
			ok = 0;
		cursor = cursor->next;
		i--;
	}
	if (i != -1 || cursor != NULL)
		ok = 0;
	if (!ok)
		printf("    " RED "[1] ft_list_push_strs() did not build the expected list (strs[0] at the end)\n" DEFAULT);
	else
		printf("  " GREEN CHECKMARK GREY " [1] ft_list_push_strs() built the expected list, with strs[0] at the end\n" DEFAULT);
	moul_free_list(list);
	return (ok ? 0 : -1);
}
