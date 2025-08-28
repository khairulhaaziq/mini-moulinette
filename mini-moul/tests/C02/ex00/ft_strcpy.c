#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../../ex00/ft_strcpy.c"
#include "../../../utils/constants.h"

typedef struct	s_test
{
	char	*desc;
	char	dest[40];
	char	*src;
	char	*expected;
}		t_test;

int	run_tests(t_test *tests, int count);

int	main(void)
{
	t_test tests[] = {
		{
			.desc = "ft_strcpy(dest[12], \"FGccjqWCcYr\")",
			.dest = {0},
			.src = "FGccjqWCcYr",
			.expected = "FGccjqWCcYr"
		},
		{
			.desc = "ft_strcpy(dest[40], \"gVepWWXynLOXqCHCscGrowUZSebdZIfy\")",
			.dest = {0},
			.src = "gVepWWXynLOXqCHCscGrowUZSebdZIfy",
			.expected = "gVepWWXynLOXqCHCscGrowUZSebdZIfy"
		},
		{
			.desc = "ft_strcpy(dest[4], \"TcXF\")",
			.dest = {0},
			.src = "TcXF",
			.expected = "TcXF"
		}
	};
	int count = sizeof(tests) / sizeof(tests[0]);

	// Fill destination buffers with 'X' so the tests will reveal whether
	// ft_strcpy actually wrote a terminating '\0' byte into the destination.
	for (int i = 0; i < count; i++)
	{
		memset(tests[i].dest, 'X', sizeof(tests[i].dest));
	}
	
	return (run_tests(tests, count));
}

int	run_tests(t_test *tests, int count)
{
	int i;
	int error = 0;
	
	for (i = 0; i < count; i++)
	{
		char *result = ft_strcpy(tests[i].dest, tests[i].src);
		
		if (strcmp(result, tests[i].expected) != 0)
		{
			printf("    " RED "[%d] %s Expected \"%s\", got \"%s\"\n", i + 1, tests[i].desc, tests[i].expected, result);
			error -= 1;
		}
		else
			printf("  " GREEN CHECKMARK GREY " [%d] %s Expected \"%s\", got \"%s\"\n" DEFAULT, i + 1, tests[i].desc, tests[i].expected, result);
	}
	return (error);
}
