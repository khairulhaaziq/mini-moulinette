#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../../ex07/ft_strupcase.c"
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
			.desc = "ft_strupcase(\"abcdefghijk\")",
			.src = "abcdefghijk",
			.expected = "ABCDEFGHIJK"
		},
		{
			.desc = "ft_strupcase(\"agsKofnkFgbsdv\")",
			.src = "agsKofnkFgbsdv",
			.expected = "AGSKOFNKFGBSDV"
		},
		{
			.desc = "ft_strupcase(\"23_-3frewg4wvfsd4\")",
			.src = "23_-3frewg4wvfsd4",
			.expected = "23_-3FREWG4WVFSD4"
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
        char *returned = ft_strupcase(result);

        if (returned != result || strcmp(result, tests[i].expected) != 0)
        {
            printf("    " RED "[%d] %s Expected \"%s\", got \"%s\" (return value: %s)\n", i + 1, tests[i].desc, tests[i].expected, result, returned == result ? "correct" : "incorrect");
            error -= 1;
        }
        else
            printf("  " GREEN CHECKMARK GREY " [%d] %s Expected \"%s\", got \"%s\"\n" DEFAULT, i + 1, tests[i].desc, tests[i].expected, result);

        free(result);
    }

    return (error);
}

