// ALLOWED_FUNCTIONS: 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../../ex10/ft_strlcpy.c"
#include "../../../utils/constants.h"

typedef struct s_test
{
    char *desc;
    char dest[40];
    char *src;
    size_t size;
    size_t expected_len;
    char *expected;
} t_test;

int run_tests(t_test *tests, int count);
int test_size_zero(void);

int main(void)
{
    t_test tests[] = {
        {.desc = "ft_strlcpy(dest[10], \"Hello!\", 7) exact fit, no truncation",
         .dest = {0},
         .src = "Hello!",
         .size = 7,
         .expected_len = 6,
         .expected = "Hello!"},
        {.desc = "ft_strlcpy(dest[10], \"World!\", 10)",
         .dest = {0},
         .src = "World!",
         .size = 10,
         .expected_len = 6,
         .expected = "World!"},
        {.desc = "ft_strlcpy(dest[10], \"Hello, World!\", 10)",
         .dest = {0},
         .src = "Hello, World!",
         .size = 10,
         .expected_len = 13,
         .expected = "Hello, Wo"},
        {.desc = "ft_strlcpy(dest[5], \"Hello, World!\", 5)",
         .dest = {0},
         .src = "Hello, World!",
         .size = 5,
         .expected_len = 13,
         .expected = "Hell"},
        {.desc = "ft_strlcpy(dest[10], \"\", 5)",
         .dest = {0},
         .src = "",
         .size = 5,
         .expected_len = 0,
         .expected = ""},
        {.desc = "ft_strlcpy(dest[1], \"Hello, World!\", 1)",
         .dest = {0},
         .src = "Hello, World!",
         .size = 1,
         .expected_len = 13,
         .expected = ""},

    };
    int count = sizeof(tests) / sizeof(tests[0]);
    int error = run_tests(tests, count);

    if (test_size_zero() != 0)
        error -= 1;
    return (error);
}

int test_size_zero(void)
{
    char dest[10];
    size_t result_len;
    int ok;

    /* with size 0, dest must be left untouched: poison it first so a
     * write of even a single null byte at dest[0] shows up */
    memset(dest, 'Z', sizeof(dest));
    result_len = ft_strlcpy(dest, "Hello", 0);

    ok = (result_len == 5 && dest[0] == 'Z');
    if (!ok)
        printf("    " RED "[size 0] ft_strlcpy(dest, \"Hello\", 0) Expected dest untouched and return 5, got dest[0]='%c' (return %zu)\n" DEFAULT, dest[0], result_len);
    else
        printf("  " GREEN CHECKMARK GREY " [size 0] ft_strlcpy(dest, \"Hello\", 0) left dest untouched and returned 5\n" DEFAULT);
    return (ok ? 0 : -1);
}

int run_tests(t_test *tests, int count)
{
    int i;
    int error = 0;

    for (i = 0; i < count; i++)
    {
        size_t result_len = ft_strlcpy(tests[i].dest, tests[i].src, tests[i].size);
        if (result_len != tests[i].expected_len || strcmp(tests[i].dest, tests[i].expected) != 0)
        {
            printf("    " RED "[%d] %s Expected \"%s\" (len %zu), got \"%s\" (len %zu)\n", i + 1, tests[i].desc, tests[i].expected, tests[i].expected_len, tests[i].dest, result_len);
            error -= 1;
        }
        else
        {
            printf("  " GREEN CHECKMARK GREY " [%d] %s Expected \"%s\" (len %zu), got \"%s\" (len %zu)\n" DEFAULT, i + 1, tests[i].desc, tests[i].expected, tests[i].expected_len, tests[i].dest, result_len);
        }
    }
    return (error);
}
