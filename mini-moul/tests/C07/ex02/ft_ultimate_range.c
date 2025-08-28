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
            .desc = "ft_ultimate_range with min 1, max 1",
            .min = 1,
            .max = 1,
            .range = NULL,
            .expected_return = 0,
            .expected_range = NULL,
        },
        {
            .desc = "ft_ultimate_range with min 1, max 2",
            .min = 1,
            .max = 2,
            .range = NULL,
            .expected_return = 1,
            .expected_range = (int[]){1},
        },
        {
            .desc = "ft_ultimate_range with min -1, max 1",
            .min = -1,
            .max = 1,
            .range = NULL,
            .expected_return = 2,
            .expected_range = (int[]){-1, 0},
        },
        {
            .desc = "ft_ultimate_range with min 0, max 1",
            .min = 0,
            .max = 1,
            .range = NULL,
            .expected_return = 1,
            .expected_range = (int[]){0},
        },
        {
            .desc = "ft_ultimate_range with min -2147483648, max -2147483647",
            .min = -2147483648,
            .max = -2147483647,
            .range = NULL,
            .expected_return = 1,
            .expected_range = (int[]){-2147483648},
        },
        {
            .desc = "ft_ultimate_range with min 2147483646, max 2147483647",
            .min = 2147483646,
            .max = 2147483647,
            .range = NULL,
            .expected_return = 1,
            .expected_range = (int[]){2147483646},
        },
        {
            .desc = "ft_ultimate_range with min -100, max 0",
            .min = -100,
            .max = 0,
            .range = NULL,
            .expected_return = 100,
            .expected_range = (int[]){ -100, -99, -98, -97, -96, -95, -94, -93, -92, -91, -90, -89, -88, -87, -86, -85, -84, -83, -82, -81, -80, -79, -78, -77, -76, -75, -74, -73, -72, -71, -70, -69, -68, -67, -66, -65, -64, -63, -62, -61, -60, -59, -58, -57, -56, -55, -54, -53, -52, -51, -50, -49, -48, -47, -46, -45, -44, -43, -42, -41, -40, -39, -38, -37, -36, -35, -34, -33, -32, -31, -30, -29, -28, -27, -26, -25, -24, -23, -22, -21, -20, -19, -18, -17, -16, -15, -14, -13, -12, -11, -10, -9, -8, -7, -6, -5, -4, -3, -2, -1, }
        },
        {
            .desc = "ft_ultimate_range with min 0, max 100",
            .min = 0,
            .max = 100,
            .range = NULL,
            .expected_return = 100,
            .expected_range = (int[]){ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, },
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
        int *result;
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
