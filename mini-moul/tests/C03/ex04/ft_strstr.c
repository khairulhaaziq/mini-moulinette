// ALLOWED_FUNCTIONS: 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../../ex04/ft_strstr.c"
#include "../../../utils/constants.h"

typedef struct s_test
{
    char *desc;
    char *str;
    char *find;
    char *expected_output;
} t_test;

int run_tests(t_test *tests, int count);

int main(void)
{
    t_test tests[] = {
        {
            .desc = "Find a substring in the middle of a string",
            .str = "42 1337 Network 2021 piscine Benguerir Khouribga",
            .find = "piscine",
            .expected_output = "piscine Benguerir Khouribga",
        },
        {
            .desc = "Find a substring at the beginning of a string",
            .str = "piscine Benguerir Khouribga",
            .find = "piscine",
            .expected_output = "piscine Benguerir Khouribga",
        },
        {
            .desc = "Find a substring at the end of a string",
            .str = "The quick brown fox jumps over the lazy dog",
            .find = "dog",
            .expected_output = "dog",
        },
        {
            .desc = "Find an empty substring in a string",
            .str = "42 1337 Network 2021 piscine Benguerir Khouribga",
            .find = "",
            .expected_output = "42 1337 Network 2021 piscine Benguerir Khouribga",
        },
        {
            .desc = "Find a substring that doesn't exist in a string",
            .str = "42 1337 Network 2021 piscine Benguerir Khouribga",
            .find = "abcd",
            .expected_output = NULL,
        },
        {
            .desc = "Find a substring with existing characters",
            .str = "-62,47 +62,47",
            .find = "-47",
            .expected_output = NULL,
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
        char *result = ft_strstr(tests[i].str, tests[i].find);
        char *result_desc = result ? result : "(null)";
        char *expected_desc = tests[i].expected_output ? tests[i].expected_output : "(null)";

        if ((result == NULL && tests[i].expected_output != NULL) || (result != NULL && strcmp(result, tests[i].expected_output) != 0))
        {
            printf("    " RED "[%d] %s Expected output \"%s\", got \"%s\"\n", i + 1, tests[i].desc, expected_desc, result_desc);
            error -= 1;
        }
        else
        {
            printf("  " GREEN CHECKMARK GREY " [%d] %s Expected output \"%s\", got \"%s\"\n" DEFAULT, i + 1, tests[i].desc, expected_desc, result_desc);
        }
    }

    return error;
}