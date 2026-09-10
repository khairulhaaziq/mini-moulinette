// ALLOWED_FUNCTIONS: malloc
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../../ex01/ft_map.c"
#include "../../../utils/constants.h"

static int moul_square(int n)
{
	return (n * n);
}

typedef struct s_test
{
	char *desc;
	int *tab;
	int length;
	int *expected;
} t_test;

int run_tests(t_test *tests, int count);

int main(void)
{
	int tab1[] = {1, 2, 3, 4, 5};
	int expected1[] = {1, 4, 9, 16, 25};
	int tab2[] = {0, -3, 7};
	int expected2[] = {0, 9, 49};
	t_test tests[] = {
		{.desc = "ft_map(square) on {1, 2, 3, 4, 5}", .tab = tab1, .length = 5, .expected = expected1},
		{.desc = "ft_map(square) on {0, -3, 7}", .tab = tab2, .length = 3, .expected = expected2},
	};
	int count = sizeof(tests) / sizeof(tests[0]);

	return (run_tests(tests, count));
}

int run_tests(t_test *tests, int count)
{
	int i;
	int j;
	int error = 0;
	int *original;

	for (i = 0; i < count; i++)
	{
		int ok = 1;
		int *result;

		original = malloc(sizeof(int) * tests[i].length);
		memcpy(original, tests[i].tab, sizeof(int) * tests[i].length);

		result = ft_map(tests[i].tab, tests[i].length, &moul_square);
		if (!result)
			ok = 0;
		else
		{
			for (j = 0; j < tests[i].length; j++)
			{
				if (result[j] != tests[i].expected[j])
				{
					ok = 0;
					break;
				}
			}
		}
		for (j = 0; j < tests[i].length; j++)
		{
			if (tests[i].tab[j] != original[j])
				ok = 0;
		}
		free(original);
		if (result)
			free(result);

		if (!ok)
		{
			printf("    " RED "[%d] %s did not return the expected mapped array\n" DEFAULT, i + 1, tests[i].desc);
			error -= 1;
		}
		else
			printf("  " GREEN CHECKMARK GREY " [%d] %s returned the expected mapped array\n" DEFAULT, i + 1, tests[i].desc);
	}
	return (error);
}
