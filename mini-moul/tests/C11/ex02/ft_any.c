// ALLOWED_FUNCTIONS: 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../../ex02/ft_any.c"
#include "../../../utils/constants.h"

static int moul_is_empty(char *s)
{
	return (s[0] == '\0');
}

typedef struct s_test
{
	char *desc;
	char **tab;
	int expected;
} t_test;

int run_tests(t_test *tests, int count);

int main(void)
{
	char *tab1[] = {"hello", "", "world", NULL};
	char *tab2[] = {"hello", "world", NULL};
	char *tab3[] = {NULL};
	char *tab4[] = {"", NULL};
	t_test tests[] = {
		{.desc = "ft_any(is_empty) with one empty string", .tab = tab1, .expected = 1},
		{.desc = "ft_any(is_empty) with no empty string", .tab = tab2, .expected = 0},
		{.desc = "ft_any(is_empty) on an empty array", .tab = tab3, .expected = 0},
		{.desc = "ft_any(is_empty) with only an empty string", .tab = tab4, .expected = 1},
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
		int result = ft_any(tests[i].tab, &moul_is_empty);

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
