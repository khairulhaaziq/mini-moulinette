// ALLOWED_FUNCTIONS: 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../../ex00/ft_strcmp.c"
#include "../../../utils/constants.h"

typedef struct s_test
{
    char *desc;
    char *s1;
    char *s2;
    int expected;
} t_test;

int run_tests(t_test *tests, int count);

int main(void)
{
    t_test tests[] = {
        {
            .desc = "Compare two equal strings",
            .s1 = "Hello",
            .s2 = "Hello",
            .expected = 0,
        },
        {
            .desc = "Compare two different strings of equal length",
            .s1 = "Hello",
            .s2 = "He",
            .expected = 108,
        },
        {
            .desc = "Compare two different strings of different length",
            .s1 = "Hello",
            .s2 = "Hello1",
            .expected = -49,
        },
        {
            .desc = "Compare two empty strings",
            .s1 = "",
            .s2 = "",
            .expected = 0,
        },
        {
            .desc = "Compare a string with an empty string",
            .s1 = "Hello",
            .s2 = "",
            .expected = 72,
        },
        {
            .desc = "Compare two strings of length 1",
            .s1 = "a",
            .s2 = "b",
            .expected = -1,
        },
        {
            .desc = "Compare two strings of length 1 (reversed)",
            .s1 = "b",
            .s2 = "a",
            .expected = 1,
        },
        {
            .desc = "Compare two strings of length 2",
            .s1 = "ab",
            .s2 = "ac",
            .expected = -1,
        },
        {
            .desc = "Compare two strings of length 2 (reversed)",
            .s1 = "ac",
            .s2 = "ab",
            .expected = 1,
        },
        {
            .desc = "Compare two strings with null character",
            .s1 = "Hello\0world",
            .s2 = "Hello",
            .expected = 0,
        },
        {
            .desc = "Compare two strings with null character (reversed)",
            .s1 = "Hello",
            .s2 = "Hello\0world",
            .expected = 0,
        },
        {
            .desc = "Compare two strings with multiple null characters",
            .s1 = "Hello\0world\0",
            .s2 = "Hello\0",
            .expected = 0,
        },
        {
            .desc = "Compare two strings with multiple null characters (reversed)",
            .s1 = "Hello\0",
            .s2 = "Hello\0world\0",
            .expected = 0,
        },
        {
            .desc = "Compare two identical strings with different pointers",
            .s1 = "Hello",
            .s2 = strdup("Hello"),
            .expected = 0,
        },
        {
            .desc = "Compare two non-identical strings with different pointers",
            .s1 = "Hello",
            .s2 = strdup("World"),
            .expected = -15,
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
        int result = ft_strcmp(tests[i].s1, tests[i].s2);

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