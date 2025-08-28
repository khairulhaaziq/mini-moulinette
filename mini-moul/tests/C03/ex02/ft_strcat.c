#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../../ex02/ft_strcat.c"
#include "../../../utils/constants.h"

typedef struct s_test
{
	char	*desc;
	char	*initial_dest;
	char	*src;
	char	*expected;
} t_test;

int run_tests(t_test *tests, int count);

int main(void)
{
	t_test tests[] = {
		{
			.desc = "Append a string to an empty string",
			.initial_dest = "",
			.src = "Hello",
			.expected = "Hello"
		},
		{
			.desc = "Append a string to a non-empty string",
			.initial_dest = "42 ",
			.src = "Network",
			.expected = "42 Network"
		},
		{
			.desc = "Append a string to itself",
			.initial_dest = "Hello",
			.src = "Hello",
			.expected = "HelloHello"
		},
		{
			.desc = "Append an empty string to a non-empty string",
			.initial_dest = "Hello",
			.src = "",
			.expected = "Hello"
		},
		{
			.desc = "Append an empty string to an empty string",
			.initial_dest = "",
			.src = "",
			.expected = ""
		}
	};
	int count = sizeof(tests) / sizeof(tests[0]);

	return (run_tests(tests, count));
}

int	run_tests(t_test *tests, int count)
{
	int i;
	int error = 0;
	int j;
	int expected_len;
	char dest[30];

	for (i = 0; i < count; i++)
	{
		strcpy(dest, tests[i].initial_dest);
		expected_len = strlen(tests[i].expected);
		
		for (j = expected_len + 1; j < expected_len + 6 && j < 29; j++)
			dest[j] = 'X';
		dest[j] = '\0';
		
		strcpy(dest, tests[i].initial_dest);
		ft_strcat(dest, tests[i].src);

		if (strcmp(dest, tests[i].expected) != 0)
		{
			printf("    " RED "[%d] No null terminator found after appending \"%s\" to \"%s\"\n", i + 1, tests[i].src, tests[i].initial_dest);
			error -= 1;
		}
		else
		{
			for (j = expected_len + 1; j < expected_len + 6 && j < 29; j++)
			{
				if (dest[j] != 'X')
				{
					printf("    " RED "[%d] %s Null termination check failed at position %d\n", i + 1, tests[i].desc, j);
					error -= 1;
					break;
				}
			}
			if (j == expected_len + 6 || j == 29)
				printf("  " GREEN CHECKMARK GREY " [%d] %s Expected \"%s\", got \"%s\"\n" DEFAULT, i + 1, tests[i].desc, tests[i].expected, dest);
		}
	}
	return (error);
}