// ALLOWED_FUNCTIONS: 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../../ex03/ft_strncat.c"
#include "../../../utils/constants.h"

typedef struct s_test
{
    char *desc;
    char *dest;
    char *src;
    size_t n;
    char *expected;
} t_test;

int run_tests(t_test *tests, int count);

int main(void)
{
    t_test tests[] = {
        {
            .desc = "Concatenate two strings",
            .dest = "Hello ",
            .src = "World",
            .n = 5,
            .expected = "Hello World",
        },
        {
            .desc = "Concatenate two empty strings",
            .dest = "",
            .src = "",
            .n = 5,
            .expected = "",
        },
        {
            .desc = "Concatenate a string with an empty string",
            .dest = "Hello",
            .src = "",
            .n = 5,
            .expected = "Hello",
        },
        {
            .desc = "Concatenate a string with another string of same length",
            .dest = "Hello",
            .src = "World",
            .n = 5,
            .expected = "HelloWorld",
        },
        {
            .desc = "Concatenate a string with another string but with n less than src length",
            .dest = "Hello",
            .src = "World",
            .n = 2,
            .expected = "HelloWo",
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
        char dest[40];
        strcpy(dest, tests[i].dest);

        char *result = ft_strncat(dest, tests[i].src, tests[i].n);

        if (result != dest || strcmp(result, tests[i].expected) != 0)
        {
            printf("    " RED "[%d] %s Expected output \"%s\", got \"%s\"\n" DEFAULT, i + 1, tests[i].desc, tests[i].expected, result);
            error -= 1;
        }
        else
        {
            printf("  " GREEN CHECKMARK GREY " [%d] %s Expected output \"%s\", got \"%s\"\n" DEFAULT, i + 1, tests[i].desc, tests[i].expected, result);
        }
    }

    return error;
}