#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../../ex04/ft_convert_base.c"
#if __has_include("../../../../ex04/ft_convert_base2.c")
# include "../../../../ex04/ft_convert_base2.c"
#endif
#include "../../../utils/constants.h"

typedef struct s_test
{
    char *desc;
    char *nbr;
    char *base_from;
    char *base_to;
    char *expected;
} t_test;

int run_tests(t_test *tests, int count);

int main(void)
{
    t_test tests[] = {
        {
            .desc = "Convert positive decimal to binary",
            .nbr = "42",
            .base_from = "0123456789",
            .base_to = "01",
            .expected = "101010",
        },
        {
            .desc = "Convert negative decimal to binary",
            .nbr = "-42",
            .base_from = "0123456789",
            .base_to = "01",
            .expected = "-101010",
        },
        {
            .desc = "Convert binary to hexadecimal",
            .nbr = "101010",
            .base_from = "01",
            .base_to = "0123456789ABCDEF",
            .expected = "2A",
        },
	/*
        {
            .desc = "Invalid base_from",
            .nbr = "42",
            .base_from = "012345678",
            .base_to = "01",
            .expected = NULL,
        },
        {
            .desc = "Invalid base_to",
            .nbr = "42",
            .base_from = "0123456789",
            .base_to = "01a",
            .expected = NULL,
        },
	*/
    };
    int count = sizeof(tests) / sizeof(tests[0]);

    return run_tests(tests, count);
}

int run_tests(t_test *tests, int count)
{
    int i;
    int error = 0;

    for (i = 0; i < count; i++)
    {
        char *result = ft_convert_base(tests[i].nbr, tests[i].base_from, tests[i].base_to);

        if (!result && !tests[i].expected)
        {
            printf(GREEN CHECKMARK GREY " [%d] %s\n" DEFAULT, i + 1, tests[i].desc);
        }
        else if (!result || !tests[i].expected)
        {
            printf(RED "[%d] %s got \"%s\" instead of \"%s\"\n" DEFAULT, i + 1, tests[i].desc, result, tests[i].expected);
            error -= 1;
        }
        else if (strcmp(result, tests[i].expected) != 0)
        {
            printf(RED "[%d] %s got \"%s\" instead of \"%s\"\n" DEFAULT, i + 1, tests[i].desc, result, tests[i].expected);
            error -= 1;
        }
        else
        {
            printf(GREEN CHECKMARK GREY " [%d] %s got \"%s\" as expected\n" DEFAULT, i + 1, tests[i].desc, result);
        }

        free(result);
    }

    return error;
}
