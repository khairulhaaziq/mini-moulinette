#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "../../../../ex06/ft_is_prime.c"
#include "../../../utils/constants.h"

typedef struct s_test
{
    char *desc;
    int n;
    int expected;
} t_test;

int run_tests(t_test *tests, int count);

int main(void)
{
    t_test tests[] = {
        {
            .desc = "Is 1 prime",
            .n = 1,
            .expected = 0,
        },
        {
            .desc = "Is 2 prime",
            .n = 2,
            .expected = 1,
        },
        {
            .desc = "Is 3 prime",
            .n = 3,
            .expected = 1,
        },
        {
            .desc = "Is 4 prime",
            .n = 4,
            .expected = 0,
        },
        {
            .desc = "Is 17 prime",
            .n = 17,
            .expected = 1,
        },
        {
            .desc = "Is 27 prime",
            .n = 27,
            .expected = 0,
        },
        {
            .desc = "Is a negative number prime",
            .n = -5,
            .expected = 0,
        },
        {
            .desc = "Is 0 prime",
            .n = 0,
            .expected = 0,
        },
        {
            .desc = "Is 5 prime",
            .n = 5,
            .expected = 1,
        },
        {
            .desc = "Is 7 prime",
            .n = 7,
            .expected = 1,
        },
        {
            .desc = "Is 9 prime",
            .n = 9,
            .expected = 0,
        },
        {
            .desc = "Is 11 prime",
            .n = 11,
            .expected = 1,
        },
        {
            .desc = "Is 13 prime",
            .n = 13,
            .expected = 1,
        },
        {
            .desc = "Is 15 prime",
            .n = 15,
            .expected = 0,
        },
        {
            .desc = "Is 19 prime",
            .n = 19,
            .expected = 1,
        },
        {
            .desc = "Is 21 prime",
            .n = 21,
            .expected = 0,
        },
        {
            .desc = "Is 25 prime",
            .n = 25,
            .expected = 0,
        },
        {
            .desc = "Is 29 prime",
            .n = 29,
            .expected = 1,
        },
        {
            .desc = "Is 49 prime",
            .n = 49,
            .expected = 0,
        },
        {
            .desc = "Is 97 prime",
            .n = 97,
            .expected = 1,
        },
        {
            .desc = "Is 100 prime",
            .n = 100,
            .expected = 0,
        },
        {
            .desc = "Is 101 prime",
            .n = 101,
            .expected = 1,
        },
        {
            .desc = "Is 121 prime",
            .n = 121,
            .expected = 0,
        },
	{
	    .desc = "Is 2147480197 prime (should not take longer than a second to test)",
	    .n = 2147480197,
	    .expected = 1,
	},
	{
	    .desc = "Is 2147480927 prime (should not take longer than a second to test)",
	    .n = 2147480927,
	    .expected = 1,
	}
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
        int result = ft_is_prime(tests[i].n);

        if (result != tests[i].expected)
        {
            printf("    " RED "[%d] %s Expected %d, got %d\n", i + 1, tests[i].desc, tests[i].expected, result);
            error -= 1;
        }
        else
        {
            printf("  " GREEN CHECKMARK GREY " [%d] %s Expected %d, got %d\n" DEFAULT, i + 1, tests[i].desc, tests[i].expected, result);
        }
    }

    return error;
}
