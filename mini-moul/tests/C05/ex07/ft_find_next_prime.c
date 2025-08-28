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
            .desc = "Next prime after 3",
            .n = 3,
            .expected = 3,
        },
        {
            .desc = "Next prime after 4",
            .n = 4,
            .expected = 5,
        },
        {
            .desc = "Next prime after 5",
            .n = 5,
            .expected = 5,
        },
        {
            .desc = "Next prime after 6",
            .n = 6,
            .expected = 7,
        },
        {
            .desc = "Next prime after 7",
            .n = 7,
            .expected = 7,
        },
        {
            .desc = "Next prime after 8",
            .n = 8,
            .expected = 11,
        },
        {
            .desc = "Next prime after 9",
            .n = 9,
            .expected = 11,
        },
        {
            .desc = "Next prime after 11",
            .n = 11,
            .expected = 11,
        },
        {
            .desc = "Next prime after 12",
            .n = 12,
            .expected = 13,
        },
        {
            .desc = "Next prime after 13",
            .n = 13,
            .expected = 13,
        },
        {
            .desc = "Next prime after 14",
            .n = 14,
            .expected = 17,
        },
        {
            .desc = "Next prime after 15",
            .n = 15,
            .expected = 17,
        },
        {
            .desc = "Next prime after 16",
            .n = 16,
            .expected = 17,
        },
        {
            .desc = "Next prime after 17",
            .n = 17,
            .expected = 17,
        },
        {
            .desc = "Next prime after 18",
            .n = 18,
            .expected = 19,
        },
        {
            .desc = "Next prime after 19",
            .n = 19,
            .expected = 19,
        },
        {
            .desc = "Next prime after 20",
            .n = 20,
            .expected = 23,
        },
        {
            .desc = "Next prime after 97",
            .n = 97,
            .expected = 97,
        },
        {
            .desc = "Next prime after 98",
            .n = 98,
            .expected = 101,
        },
        {
            .desc = "Next prime after 100",
            .n = 100,
            .expected = 101,
        },
        {
            .desc = "Next prime after 101",
            .n = 101,
            .expected = 101,
        },
        {
            .desc = "Next prime after 120",
            .n = 120,
            .expected = 127,
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
