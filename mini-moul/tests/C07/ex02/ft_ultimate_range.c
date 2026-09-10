// ALLOWED_FUNCTIONS: malloc
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../../ex02/ft_ultimate_range.c"
#include "../../../utils/constants.h"

typedef struct s_test
{
    char *desc;
    int min;
    int max;
    int **range;
    int expected_return;
    int *expected_range;
} t_test;

int run_tests(t_test *tests, int count);

int main(void)
{
    t_test tests[] = {
        {
            .desc = "ft_ultimate_range with min 0, max 0",
            .min = 0,
            .max = 0,
            .range = NULL,
            .expected_return = 0,
            .expected_range = NULL,
        },
        {
            .desc = "ft_ultimate_range with min 0, max 5",
            .min = 0,
            .max = 5,
            .range = NULL,
            .expected_return = 5,
            .expected_range = (int[]){0, 1, 2, 3, 4},
        },
        {
            .desc = "ft_ultimate_range with min -5, max 5",
            .min = -5,
            .max = 5,
            .range = NULL,
            .expected_return = 10,
            .expected_range = (int[]){-5, -4, -3, -2, -1, 0, 1, 2, 3, 4},
        },
        {
            .desc = "ft_ultimate_range with min -10, max -5",
            .min = -10,
            .max = -5,
            .range = NULL,
            .expected_return = 5,
            .expected_range = (int[]){-10, -9, -8, -7, -6},
        },
        {
            .desc = "ft_ultimate_range with max less than min",
            .min = 10,
            .max = 5,
            .range = NULL,
            .expected_return = 0,
            .expected_range = NULL,
        },
        {
            .desc = "ft_ultimate_range with both min and max equal to 2147483647",
            .min = 2147483647,
            .max = 2147483647,
            .range = NULL,
            .expected_return = 0,
            .expected_range = NULL,
        },
        {
            .desc = "ft_ultimate_range with both min and max equal to -2147483648",
            .min = -2147483648,
            .max = -2147483648,
            .range = NULL,
            .expected_return = 0,
            .expected_range = NULL,
        },
        {
            .desc = "ft_ultimate_range with a single-element range at the top boundary",
            .min = 2147483646,
            .max = 2147483647,
            .range = NULL,
            .expected_return = 1,
            .expected_range = (int[]){2147483646},
        },
        {
            .desc = "ft_ultimate_range with a single-element range at the bottom boundary",
            .min = -2147483648,
            .max = -2147483647,
            .range = NULL,
            .expected_return = 1,
            .expected_range = (int[]){-2147483648},
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
        /* start from NULL: a buggy implementation that never writes
         * through the out-parameter leaves free() a safe no-op instead
         * of crashing on garbage stack memory */
        int *result = NULL;
        int expected_size = (tests[i].max - tests[i].min);

        int range_size = ft_ultimate_range(&result, tests[i].min, tests[i].max);

        if (tests[i].expected_range == NULL && result == NULL)
        {
            printf("  " GREEN CHECKMARK GREY " [%d] %s Expected NULL, got NULL\n" DEFAULT, i + 1, tests[i].desc);
        }
        else if (tests[i].expected_range == NULL || result == NULL)
        {
            printf("    " RED "[%d] %s Expected %p, got %p\n" DEFAULT, i + 1, tests[i].desc, tests[i].expected_range, result);
            error--;
        }
        else if (range_size != expected_size)
        {
            printf("    " RED "[%d] %s Expected size %d, got size %d\n" DEFAULT, i + 1, tests[i].desc, expected_size, range_size);
            error--;
        }
        else if (memcmp(result, tests[i].expected_range, expected_size * sizeof(int)) != 0)
        {
            printf("    " RED "[%d] %s Expected { ", i + 1, tests[i].desc);
            for (int j = 0; j < expected_size; j++)
            {
                printf("%d, ", tests[i].expected_range[j]);
            }
            printf("}, got { ");
            for (int j = 0; j < expected_size; j++)
            {
                printf("%d, ", result[j]);
            }
            printf("}\n" DEFAULT);
            error--;
        }
        else
        {
            printf("  " GREEN CHECKMARK GREY " [%d] %s Passed\n" DEFAULT, i + 1, tests[i].desc);
        }

        free(result);
    }

    return error;
}