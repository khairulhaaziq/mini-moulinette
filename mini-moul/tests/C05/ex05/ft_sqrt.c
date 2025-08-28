#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "../../../../ex05/ft_sqrt.c"
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
            .desc = "Square root of 16",
            .n = 16,
            .expected = 4,
        },
        {
            .desc = "Square root of 0",
            .n = 0,
            .expected = 0,
        },
        {
            .desc = "Square root of 1",
            .n = 1,
            .expected = 1,
        },
        {
            .desc = "Square root of 2",
            .n = 2,
            .expected = 0,
        },
        {
            .desc = "Square root of a negative number",
            .n = -5,
            .expected = 0,
        },
        {
        	.desc = "Square root of INT_MAX",
         	.n = 2147483647,
         	.expected = 0,
        },
        {
        	.desc = "Square root of number with no root",
         	.n = 1512,
          	.expected = 0,
        },
        {
            .desc = "Square root of 4",
            .n = 4,
            .expected = 2,
        },
        {
            .desc = "Square root of 9",
            .n = 9,
            .expected = 3,
        },
        {
            .desc = "Square root of 25",
            .n = 25,
            .expected = 5,
        },
        {
            .desc = "Square root of 100",
            .n = 100,
            .expected = 10,
        },
        {
            .desc = "Square root of 121",
            .n = 121,
            .expected = 11,
        },
        {
            .desc = "Square root of 144",
            .n = 144,
            .expected = 12,
        },
        {
            .desc = "Square root of 169",
            .n = 169,
            .expected = 13,
        },
        {
            .desc = "Square root of 196",
            .n = 196,
            .expected = 14,
        },
        {
            .desc = "Square root of 225",
            .n = 225,
            .expected = 15,
        },
        {
            .desc = "Square root of 46340 squared",
            .n = 2147395600,
            .expected = 46340,
        },
        {
            .desc = "Square root of 46341 squared (overflow)",
            .n = 2147483647,
            .expected = 0,
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
        int result = ft_sqrt(tests[i].n);

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
