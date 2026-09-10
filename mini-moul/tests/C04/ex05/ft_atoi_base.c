// ALLOWED_FUNCTIONS: 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../../ex05/ft_atoi_base.c"
#include "../../../utils/constants.h"

typedef struct s_test
{
    char *desc;
    char *str;
    char *base;
    int expected_output;
} t_test;

int run_tests(t_test *tests, int count);

int main(void)
{
    t_test tests[] = {
        {
            .desc = "Convert a binary number to decimal",
            .str = "101101",
            .base = "01",
            .expected_output = 45,
        },
        {
            .desc = "Convert a hexadecimal number to decimal",
            .str = "ff",
            .base = "0123456789abcdef",
            .expected_output = 255,
        },
        {
            .desc = "Convert a number with leading whitespace and sign to decimal",
            .str = "    +-14353",
            .base = "0123456789",
            .expected_output = -14353,
        },
        {
            .desc = "Convert a binary number with leading whitespace and sign to decimal",
            .str = "         ---10101001",
            .base = "01",
            .expected_output = -169,
        },
        {
            .desc = "Convert a hexadecimal number with leading whitespace and sign to decimal",
            .str = "     +---59",
            .base = "0123456789abcdef",
            .expected_output = -89,
        },
        // Add more test cases here
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
        int result = ft_atoi_base(tests[i].str, tests[i].base);
        if (result != tests[i].expected_output)
        {
            printf("    " RED "[%d] %s Expected %d, got %d\n" DEFAULT, i + 1, tests[i].desc, tests[i].expected_output, result);
            error -= 1;
        }
        else
            printf("  " GREEN CHECKMARK GREY " [%d] %s output %d as expected\n" DEFAULT, i + 1, tests[i].desc, result);
    }

    return (error);
}