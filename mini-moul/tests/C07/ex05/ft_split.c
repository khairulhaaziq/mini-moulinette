// ALLOWED_FUNCTIONS: malloc
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../../ex05/ft_split.c"
#include "../../../utils/constants.h"

typedef struct s_test
{
    char *desc;
    char *str;
    char *charset;
    char **expected;
} t_test;

int run_tests(t_test *tests, int count);

int main(void)
{
    t_test tests[] = {
       {
            .desc = "Empty string with empty charset",
            .str = "",
            .charset = "",
            .expected = (char *[1]) {0},
        },
        {
            .desc = "Single-word string with empty charset",
            .str = "hello",
            .charset = "",
            .expected = (char *[2]) {"hello", 0},
        },
        {
            .desc = "String with leading and trailing separators",
            .str = ",,hello,world,,",
            .charset = ",",
            .expected = (char *[3]) {"hello", "world", 0},
        },
        {
            .desc = "String with multiple consecutive separators",
            .str = "hello,,,,world",
            .charset = ",",
            .expected = (char *[3]) {"hello", "world", 0},
        },
        {
            .desc = "String with repeated separators",
            .str = "aaabbbaaaccc",
            .charset = "ab",
            .expected = (char *[]){ "ccc", 0 },
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
        char **result = ft_split(tests[i].str, tests[i].charset);

        if (!result && !tests[i].expected)
        {
            printf(GREEN CHECKMARK GREY " [%d] %s\n" DEFAULT, i + 1, tests[i].desc);
        }
        else if (!result || !tests[i].expected)
        {
            printf(RED "[%d] %s got \"", i + 1, tests[i].desc);
            if (result)
            {
                printf("%s", result[0]);
                for (int j = 1; result[j]; j++)
                {
                    printf("\", \"%s", result[j]);
                }
            }
            else
            {
                printf("(null)");
            }
            printf("\" instead of \"");
            if (tests[i].expected)
            {
                printf("%s", tests[i].expected[0]);
                for (int j = 1; tests[i].expected[j]; j++)
                {
                    printf("\", \"%s", tests[i].expected[j]);
                }
            }
            else
            {
                printf("(null)");
            }
            printf("\"\n" DEFAULT);
            error -= 1;
        }
        else
        {
            int j = 0;
            while (tests[i].expected[j] && result[j])
            {
                if (strcmp(tests[i].expected[j], result[j]) != 0)
                {
                    printf(RED "[%d] %s Element %d: expected \"%s\", got \"%s\"\n" DEFAULT, i + 1, tests[i].desc, j, tests[i].expected[j], result[j]);
                    error -= 1;
                    break;
                }
                j++;
            }

            if (tests[i].expected[j] != result[j])
            {
                printf(RED "[%d] %s got \"", i + 1, tests[i].desc);
                if (result)
                {
                    printf("%s", result[0]);
                    for (int j = 1; result[j]; j++)
                    {
                        printf("\", \"%s", result[j]);
                    }
                }
                else
                {
                    printf("(null)");
                }
                printf("\" instead of \"");
                if (tests[i].expected)
                {
                    printf("%s", tests[i].expected[0]);
                    for (int j = 1; tests[i].expected[j]; j++)
                    {
                        printf("\", \"%s", tests[i].expected[j]);
                    }
                }
                else
                {
                    printf("(null)");
                }
                printf("\"\n" DEFAULT);
                error -= 1;
            }
            else
            {
                printf(GREEN CHECKMARK GREY " [%d] %s got \"", i + 1, tests[i].desc);
                if (result)
                {
                    printf("%s", result[0]);
                    for (int j = 1; result[j]; j++)
                    {
                        printf("\", \"%s", result[j]);
                    }
                }
                printf("\" as expected\n" DEFAULT);
            }
        }

        if (result)
        {
            int j = 0;
            while (result[j])
            {
                free(result[j]);
                j++;
            }
            free(result);
        }
    }

    return (error);
}