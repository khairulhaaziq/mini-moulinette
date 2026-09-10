// ALLOWED_FUNCTIONS: 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../../ex03/ft_count_if.c"
#include "../../../utils/constants.h"

static int moul_is_long(char *s)
{
	return ((int)strlen(s) > 3);
}

typedef struct s_test
{
	char *desc;
	char **tab;
	int length;
	int expected;
} t_test;

int run_tests(t_test *tests, int count);

int main(void)
{
	char *tab1[] = {"hi", "hello", "yo", "world"};
	char *tab2[] = {"a", "bb", "ccc"};
	char *tab3[] = {"long", "words", "here", "too"};
	t_test tests[] = {
		{.desc = "ft_count_if(is_long) on {hi, hello, yo, world}", .tab = tab1, .length = 4, .expected = 2},
		{.desc = "ft_count_if(is_long) on {a, bb, ccc}", .tab = tab2, .length = 3, .expected = 0},
		{.desc = "ft_count_if(is_long) on {long, words, here, too}", .tab = tab3, .length = 4, .expected = 3},
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
		int result = ft_count_if(tests[i].tab, tests[i].length, &moul_is_long);

		if (result != tests[i].expected)
		{
			printf("    " RED "[%d] %s Expected %d, got %d\n" DEFAULT, i + 1, tests[i].desc, tests[i].expected, result);
			error -= 1;
		}
		else
			printf("  " GREEN CHECKMARK GREY " [%d] %s Expected %d, got %d\n" DEFAULT, i + 1, tests[i].desc, tests[i].expected, result);
	}
	return (error);
}
