// ALLOWED_FUNCTIONS: 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../../ex05/ft_str_is_uppercase.c"
#include "../../../utils/constants.h"

typedef struct	s_test
{
	char	*str;
	int		expected;
}				t_test;

int	run_tests(t_test *tests, int count);

int	main(void)
{
	t_test tests[] = {
		{
			.str = "ABCDEFGH",
			.expected = 1
		},
		{
			.str = "ABCDEFGHaI",
			.expected = 0
		},
		{
			.str = "-_134556ABCDEFGaH67",
			.expected = 0
		}
	};
	int count = sizeof(tests) / sizeof(tests[0]);
	
	return (run_tests(tests, count));
}

int	run_tests(t_test *tests, int count)
{
	int i;
	int error = 0;
	
	for (i = 0; i < count; i++)
	{
		int result = ft_str_is_uppercase(tests[i].str);
		
		if (result != tests[i].expected)
		{
			printf("    " RED "[%d] ft_str_is_uppercase(\"%s\") Expected %d, got %d\n" DEFAULT, i + 1, tests[i].str, tests[i].expected, result);
			error -= 1;
		}
		else
			printf("  " GREEN CHECKMARK GREY " [%d] ft_str_is_uppercase(\"%s\") Expected %d, got %d\n" DEFAULT, i + 1, tests[i].str, tests[i].expected, result);
	}
	return (error);
}
