// ALLOWED_FUNCTIONS: 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../../ex01/ft_strncmp.c"
#include "../../../utils/constants.h"

typedef struct s_test
{
    char *desc;
    char *s1;
    char *s2;
    size_t n;
    int expected;
} t_test;

int run_tests(t_test *tests, int count);

int main(void)
{
    t_test tests[] = {
        {
            .desc = "Comparing empty strings with n > 0",
            .s1 = "",
            .s2 = "",
            .n = 1,
            .expected = 0,
        },
        {
            .desc = "Comparing non-empty string with empty string",
            .s1 = "Hello",
            .s2 = "",
            .n = 3,
            .expected = 'H',
        },
        {
            .desc = "Comparing empty string with non-empty string",
            .s1 = "",
            .s2 = "World",
            .n = 4,
            .expected = -87,
        },
        {
            .desc = "Comparing same string with n = 0",
            .s1 = "Hello",
            .s2 = "Hello",
            .n = 0,
            .expected = 0,
        },
        {
            .desc = "Comparing strings with different character case",
            .s1 = "Hello",
            .s2 = "hELLO",
            .n = 3,
            .expected = -32,
        },
        {
            .desc = "Comparing strings with different character case",
            .s1 = "Hello",
            .s2 = "hELLO",
            .n = 4,
            .expected = -32,
        },
        {
            .desc = "Comparing strings with different character case",
            .s1 = "Hello",
            .s2 = "hELLO",
            .n = 5,
            .expected = -32,
        },
        {
            .desc = "Comparing same string with n > length of string",
            .s1 = "Hello",
            .s2 = "Hello",
            .n = 6,
            .expected = 0,
        },
        {
            .desc = "Comparing different string with n > length of string",
            .s1 = "Hello",
            .s2 = "World",
            .n = 6,
            .expected = -15,
        },
        {
            .desc = "Comparing different string with n > length of both strings",
            .s1 = "Hello",
            .s2 = "World",
            .n = 10,
            .expected = -15,
        },
        {
            .desc = "Comparing strings where n is smaller than s1",
            .s1 = "Hello",
            .s2 = "World",
            .n = 3,
            .expected = -15,
        },
        {
            .desc = "Comparing strings where n is smaller than s2",
            .s1 = "Hello",
            .s2 = "World",
            .n = 2,
            .expected = -1,
        },
        {
            .desc = "Comparing empty strings with n smaller than 1",
            .s1 = "",
            .s2 = "",
            .n = 0,
            .expected = 0,
        },
        {
            .desc = "Comparing empty string and non-empty string with n smaller than 1",
            .s1 = "",
            .s2 = "Hello",
            .n = 0,
            .expected = 0,
        },
        {
            .desc = "Comparing non-empty string and empty string with n smaller than 1",
            .s1 = "Hello",
            .s2 = "",
            .n = 0,
            .expected = 0,
        },
        {
            .desc = "Comparing equal strings with n = 0",
            .s1 = "Hello",
            .s2 = "Hello",
            .n = 0,
            .expected = 0,
        },
        {
            .desc = "Comparing different strings with n = 0",
            .s1 = "Hello",
            .s2 = "World",
            .n = 0,
            .expected = 0,
        },
        {
            .desc = "Comparing equal strings with n > string length",
            .s1 = "Hello",
            .s2 = "Hello",
            .n = 10,
            .expected = 0,
        },
        {
            .desc = "Comparing different strings with n > string length",
            .s1 = "Hello",
            .s2 = "World",
            .n = 10,
            .expected = -87,
        },
        {
            .desc = "Comparing strings with same prefix and n < string length",
            .s1 = "Hello",
            .s2 = "HelloWorld",
            .n = 2,
            .expected = 0,
        },
        {
            .desc = "Comparing strings with different prefix and n < string length",
            .s1 = "Hello",
            .s2 = "WorldHello",
            .n = 5,
            .expected = -15,
        },
        {
            .desc = "Comparing empty string with non-empty string",
            .s1 = "",
            .s2 = "Hello",
            .n = 5,
            .expected = -72,
        },
        {
            .desc = "Comparing non-empty string with empty string",
            .s1 = "Hello",
            .s2 = "",
            .n = 5,
            .expected = 72,
        },
        {
            .desc = "Comparing string with different ends and n is smaller than size",
            .s1 = "Hello",
            .s2 = "Hellz",
            .n = 4,
            .expected = 0,
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
        int result = ft_strncmp(tests[i].s1, tests[i].s2, tests[i].n);

        if ((result < 0 && tests[i].expected >= 0) || (result > 0 && tests[i].expected <= 0) || (result == 0 && tests[i].expected != 0))
        {
            printf(RED " [%d] %s: expected %s, got %d\n" DEFAULT, i + 1, tests[i].desc, (tests[i].expected < 0 ? "negative value" : (tests[i].expected > 0 ? "positive value" : "0")), result);
            error -= 1;
        }
        else
        {
            printf("  " GREEN CHECKMARK GREY " [%d] %s: expected %s, got %d\n" DEFAULT, i + 1, tests[i].desc, (tests[i].expected < 0 ? "negative value" : (tests[i].expected > 0 ? "positive value" : "0")), result);
        }
    }

    return error;
}