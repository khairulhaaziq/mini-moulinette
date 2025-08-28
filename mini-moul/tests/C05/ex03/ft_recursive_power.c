#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "../../../../ex03/ft_recursive_power.c"
#include "../../../utils/constants.h"

typedef struct s_test
{
    char *desc;
    int base;
    int power;
    int expected;
} t_test;

int run_tests(t_test *tests, int count);

int main(void)
{
    t_test tests[] = {
        {
            .desc = "Power of 0",
            .base = 10,
            .power = 0,
            .expected = 1,
        },
        {
            .desc = "Power of 1",
            .base = 2,
            .power = 1,
            .expected = 2,
        },
        {
            .desc = "Power of 2",
            .base = 3,
            .power = 2,
            .expected = 9,
        },
        {
            .desc = "Power of a negative number",
            .base = -2,
            .power = 3,
            .expected = -8,
        },
        {
            .desc = "Power of a number with a negative power",
            .base = 2,
            .power = -3,
            .expected = 0,
        },
        {
            .desc = "0 power 0 (edge case)",
            .base = 0,
            .power = 0,
            .expected = 1,
        },
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
        int result = ft_recursive_power(tests[i].base, tests[i].power);

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
