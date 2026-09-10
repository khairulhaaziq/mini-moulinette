// ALLOWED_FUNCTIONS: 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../../ex07/ft_advanced_sort_string_tab.c"
#include "../../../utils/constants.h"

static int moul_strcmp(char *a, char *b)
{
	return (strcmp(a, b));
}

static int moul_strcmp_rev(char *a, char *b)
{
	return (strcmp(b, a));
}

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
	int (*cmp)(char *, char *);
	int ascending;
} t_test;

int run_tests(t_test *tests, int count);

int main(void)
{
	char *tab1[] = {"banana", "apple", "cherry", "date", NULL};
	char *tab2[] = {"banana", "apple", "cherry", "date", NULL};
	char *tab3[] = {"zebra", "yak", "ant", NULL};
	t_test tests[] = {
		{.desc = "ft_advanced_sort_string_tab ascending (ft_strcmp)", .tab = tab1, .length = 4, .cmp = &moul_strcmp, .ascending = 1},
		{.desc = "ft_advanced_sort_string_tab descending (reverse cmp)", .tab = tab2, .length = 4, .cmp = &moul_strcmp_rev, .ascending = 0},
		{.desc = "ft_advanced_sort_string_tab ascending on {zebra, yak, ant}", .tab = tab3, .length = 3, .cmp = &moul_strcmp, .ascending = 1},
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

		ft_advanced_sort_string_tab(tests[i].tab, tests[i].cmp);

		for (j = 0; j + 1 < length; j++)
		{
			int cmp_result = strcmp(tests[i].tab[j], tests[i].tab[j + 1]);

			if (tests[i].ascending && cmp_result > 0)
				ok = 0;
			if (!tests[i].ascending && cmp_result < 0)
				ok = 0;
		}
		if (tests[i].tab[length] != NULL)
			ok = 0;
		if (!moul_same_pointer_set(before, tests[i].tab, length))
			ok = 0;

		if (!ok)
		{
			printf("    " RED "[%d] %s did not sort correctly by exchanging pointers\n" DEFAULT, i + 1, tests[i].desc);
			error -= 1;
		}
		else
			printf("  " GREEN CHECKMARK GREY " [%d] %s sorted correctly by exchanging pointers\n" DEFAULT, i + 1, tests[i].desc);
	}
	return (error);
}
