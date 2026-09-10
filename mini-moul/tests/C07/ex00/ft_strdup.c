// ALLOWED_FUNCTIONS: malloc
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../../ex00/ft_strdup.c"
#include "../../../utils/constants.h"

typedef struct s_test
{
    char *desc;
    char *src;
    char *expected;
} t_test;

int run_tests(t_test *tests, int count);

int main(void)
{
    t_test tests[] = {
        {
            .desc = "ft_strdup with empty string",
            .src = "",
            .expected = ""
        },
        {
            .desc = "ft_strdup with non-empty string",
            .src = "test",
            .expected = "test"
        },
        {
            .desc = "ft_strdup with long string",
            .src = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()",
            .expected = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()"
        },
        {
            .desc = "ft_strdup with string containing a NULL character",
            .src = "test\0test",
            .expected = "test"
        },
    };
    int count = sizeof(tests) / sizeof(tests[0]);

    return (run_tests(tests, count));
}

int run_tests(t_test *tests, int count)
{
    int i;
    int error = 0;

    for (i = 0; i < count; i++)
    {
        char *result = ft_strdup(tests[i].src);

        if (tests[i].src == NULL && result != NULL)
        {
            printf("    " RED "[%d] %s Expected NULL, got \"%s\"\n" DEFAULT, i + 1, tests[i].desc, result);
            error -= 1;
        }
        else if (tests[i].src == NULL && result == NULL)
        {
            printf("  " GREEN CHECKMARK GREY " [%d] %s output NULL as expected\n" DEFAULT, i + 1, tests[i].desc);
        }
        else if (strcmp(result, tests[i].expected) != 0)
        {
            printf("    " RED "[%d] %s Expected \"%s\", got \"%s\"\n" DEFAULT, i + 1, tests[i].desc, tests[i].expected, result);
            error -= 1;
        }
        else
            printf("  " GREEN CHECKMARK GREY " [%d] %s output \"%s\" as expected\n" DEFAULT, i + 1, tests[i].desc, result);

        free(result);
    }
    return (error);
}
