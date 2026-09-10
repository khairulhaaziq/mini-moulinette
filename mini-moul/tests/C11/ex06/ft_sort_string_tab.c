// ALLOWED_FUNCTIONS: 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../../ex06/ft_sort_string_tab.c"
#include "../../../utils/constants.h"

static int moul_same_pointer_set(char **before, char **after, int n)
{
	int i;
	int j;
	int found;

	i = 0;
	while (i < n)
	{
		found = 0;
		j = 0;
		while (j < n)
		{
			if (before[i] == after[j])
				found = 1;
			j++;
		}
		if (!found)
			return (0);
		i++;
	}
	return (1);
}

typedef struct s_test
{
	char *desc;
	char **tab;
	int length;
} t_test;

int run_tests(t_test *tests, int count);

int main(void)
{
	char *tab1[] = {"banana", "apple", "cherry", "date", NULL};
	char *tab2[] = {"zebra", "yak", "ant", NULL};
	char *tab3[] = {"same", "same", "same", NULL};
	char *tab4[] = {NULL};
	t_test tests[] = {
		{.desc = "ft_sort_string_tab on {banana, apple, cherry, date}", .tab = tab1, .length = 4},
		{.desc = "ft_sort_string_tab on {zebra, yak, ant}", .tab = tab2, .length = 3},
		{.desc = "ft_sort_string_tab on {same, same, same}", .tab = tab3, .length = 3},
		{.desc = "ft_sort_string_tab on an empty array", .tab = tab4, .length = 0},
	};
	int count = sizeof(tests) / sizeof(tests[0]);

	return (run_tests(tests, count));
}

int run_tests(t_test *tests, int count)
{
	int i;
	int j;
	int error = 0;
	char *before[16];

	for (i = 0; i < count; i++)
	{
		int ok = 1;
		int length = tests[i].length;

		for (j = 0; j < length; j++)
			before[j] = tests[i].tab[j];

		ft_sort_string_tab(tests[i].tab);

		for (j = 0; j + 1 < length; j++)
		{
			if (strcmp(tests[i].tab[j], tests[i].tab[j + 1]) > 0)
				ok = 0;
		}
		if (tests[i].tab[length] != NULL)
			ok = 0;
		if (!moul_same_pointer_set(before, tests[i].tab, length))
			ok = 0;

		if (!ok)
		{
			printf("    " RED "[%d] %s did not sort by exchanging pointers correctly\n" DEFAULT, i + 1, tests[i].desc);
			error -= 1;
		}
		else
			printf("  " GREEN CHECKMARK GREY " [%d] %s sorted by exchanging pointers correctly\n" DEFAULT, i + 1, tests[i].desc);
	}
	return (error);
}
