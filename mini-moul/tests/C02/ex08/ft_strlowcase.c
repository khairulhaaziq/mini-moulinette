// ALLOWED_FUNCTIONS: 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../../ex08/ft_strlowcase.c"
#include "../../../utils/constants.h"

typedef struct	s_test
{
	char	*desc;
	char	*src;
	char	*expected;
}		t_test;

int	run_tests(t_test *tests, int count);

int	main(void)
{
	t_test tests[] = {
		{
			.desc = "ft_strlowcase(\"ABCDEFGHIJK\")",
			.src = "ABCDEFGHIJK",
			.expected = "abcdefghijk"
		},
		{
			.desc = "ft_strlowcase(\"agsKofnkFgbsdv\")",
			.src = "agsKofnkFgbsdv",
			.expected = "agskofnkfgbsdv"
		},
		{
			.desc = "ft_strlowcase(\"23_-3FREWG4WVFSD4\")",
			.src = "23_-3FREWG4WVFSD4",
			.expected = "23_-3frewg4wvfsd4"
		},
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
        char *result = malloc(sizeof(char) * (strlen(tests[i].src) + 1));
        if (result == NULL)
        {
            perror("Error: malloc failed");
            exit(EXIT_FAILURE);
        }

        strcpy(result, tests[i].src);
        ft_strlowcase(result);

        if (strcmp(result, tests[i].expected) != 0)
        {
            printf("    " RED "[%d] %s Expected \"%s\", got \"%s\"\n", i + 1, tests[i].desc, tests[i].expected, result);
            error -= 1;
        }
        else
            printf("  " GREEN CHECKMARK GREY " [%d] %s Expected \"%s\", got \"%s\"\n" DEFAULT, i + 1, tests[i].desc, tests[i].expected, result);

        free(result);
    }

    return (error);
}

