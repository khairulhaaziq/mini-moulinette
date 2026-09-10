// ALLOWED_FUNCTIONS: malloc
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../../ex01/ft_range.c"
#include "../../../utils/constants.h"

typedef struct s_test
{
        char *desc;
        int min;
        int max;
        int *expected;
} t_test;

int run_tests(t_test *tests, int count);

int main(void)
{
        t_test tests[] = {
            {.desc = "ft_range with min 0, max 0",
             .min = 0,
             .max = 0,
             .expected = NULL},
            {.desc = "ft_range with min 0, max 5",
             .min = 0,
             .max = 5,
             .expected = (int[]){0, 1, 2, 3, 4}},
            {.desc = "ft_range with min -5, max 5",
             .min = -5,
             .max = 5,
             .expected = (int[]){-5, -4, -3, -2, -1, 0, 1, 2, 3, 4}},
            {.desc = "ft_range with min -10, max -5",
             .min = -10,
             .max = -5,
             .expected = (int[]){-10, -9, -8, -7, -6}},
            {.desc = "ft_range with min 5, max 0",
             .min = 5,
             .max = 0,
             .expected = NULL},
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
                int *result = ft_range(tests[i].min, tests[i].max);
                int expected_size = (tests[i].expected == NULL) ? 0 : (tests[i].max - tests[i].min);

                if (tests[i].min >= tests[i].max)
                {
                        if (result != NULL)
                        {
                                printf("    " RED "[%d] %s Expected NULL, got %p\n" DEFAULT, i + 1, tests[i].desc, result);
                                error -= 1;
                        }else
                        {
                                printf("  " GREEN CHECKMARK GREY " [%d] %s Expected NULL, got NULL\n" DEFAULT, i + 1, tests[i].desc);
                        }
                }
                else if (tests[i].expected == NULL)
                {
                        if (result != NULL)
                        {
                                printf("    " RED "[%d] %s Expected NULL, got %p\n" DEFAULT, i + 1, tests[i].desc, result);
                                error -= 1;
                        }
                }
                else if (memcmp(result, tests[i].expected, expected_size) != 0)
                {
                        printf("    " RED "[%d] %s Expected %d, got %d\n" DEFAULT, i + 1, tests[i].desc, *tests[i].expected, result[0]);
                        error -= 1;
                }
                else
                {
                        printf("  " GREEN CHECKMARK GREY " [%d] %s Expected %d, got %d\n" DEFAULT, i + 1, tests[i].desc, *tests[i].expected, result[0]);
                }

                free(result);
        }

        return (error);
}