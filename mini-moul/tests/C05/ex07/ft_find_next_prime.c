// ALLOWED_FUNCTIONS: 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "../../../../ex07/ft_find_next_prime.c"
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
            .desc = "Next prime after 0",
            .n = 0,
            .expected = 2,
        },
        {
            .desc = "Next prime after 1",
            .n = 1,
            .expected = 2,
        },
        {
            .desc = "Next prime after 2",
            .n = 2,
            .expected = 2,
        },
        {
            .desc = "Next prime after 10",
            .n = 10,
            .expected = 11,
        },
        {
            .desc = "Next prime after a negative number",
            .n = -5,
            .expected = 2,
        },
        {
            .desc = "Next prime after 17 (already prime)",
            .n = 17,
            .expected = 17,
        },
        {
            .desc = "Next prime after 24",
            .n = 24,
            .expected = 29,
        },
        {
            .desc = "Next prime after 90",
            .n = 90,
            .expected = 97,
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
        int result = ft_find_next_prime(tests[i].n);

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