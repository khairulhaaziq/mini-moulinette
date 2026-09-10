// ALLOWED_FUNCTIONS: 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../../ex04/ft_is_sort.c"
#include "../../../utils/constants.h"

static int moul_cmp_int(int a, int b)
{
	return (a - b);
}

typedef struct s_test
{
	char *desc;
	int *tab;
	int length;
	int expected;
} t_test;

int run_tests(t_test *tests, int count);

int main(void)
{
	int tab1[] = {1, 2, 3, 4, 5};
	int tab2[] = {5, 3, 4, 1, 2};
	int tab3[] = {1, 1, 2, 2, 3};
	int tab4[] = {42};
	int tab5[] = {0};
	int tab6[] = {3, 2, 1};
	t_test tests[] = {
		{.desc = "ft_is_sort on a sorted array", .tab = tab1, .length = 5, .expected = 1},
		{.desc = "ft_is_sort on an unsorted array", .tab = tab2, .length = 5, .expected = 0},
		{.desc = "ft_is_sort on a sorted array with duplicates", .tab = tab3, .length = 5, .expected = 1},
		{.desc = "ft_is_sort on a single-element array", .tab = tab4, .length = 1, .expected = 1},
		{.desc = "ft_is_sort on an empty array", .tab = tab5, .length = 0, .expected = 1},
		{.desc = "ft_is_sort on a descending array", .tab = tab6, .length = 3, .expected = 0},
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
		int result = ft_is_sort(tests[i].tab, tests[i].length, &moul_cmp_int);

		if ((result != 0) != (tests[i].expected != 0))
		{
			printf("    " RED "[%d] %s Expected %d, got %d\n" DEFAULT, i + 1, tests[i].desc, tests[i].expected, result);
			error -= 1;
		}
		else
			printf("  " GREEN CHECKMARK GREY " [%d] %s Expected %d, got %d\n" DEFAULT, i + 1, tests[i].desc, tests[i].expected, result);
	}
	return (error);
}
