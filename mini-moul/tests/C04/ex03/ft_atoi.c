#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../../ex03/ft_atoi.c"
#include "../../../utils/constants.h"

typedef struct s_test
{
    char *desc;
    char *input;
    int expected;
} t_test;

int run_tests(t_test *tests, int count);

int main(void)
{
    t_test tests[] = {
        {
            .desc = "Convert positive integer",
            .input = "12345",
            .expected = 12345,
        },
        {
            .desc = "Convert negative integer",
            .input = "-54321",
            .expected = -54321,
        },
        {
            .desc = "Convert integer with leading spaces",
            .input = "    4567",
            .expected = 4567,
        },
        {
            .desc = "Convert integer with leading plus sign",
            .input = "+6789",
            .expected = 6789,
        },
        {
            .desc = "Convert integer with non-numeric suffix",
            .input = "123abc",
            .expected = 123,
        },
        {
            .desc = "Convert positive zero",
            .input = "0",
            .expected = 0,
        },
        {
            .desc = "Convert negative zero",
            .input = "-0",
            .expected = 0,
        },
        {
            .desc = "Convert integer with leading zeros",
            .input = "000123",
            .expected = 123,
        },
        {
            .desc = "Convert integer with leading zeros and plus sign",
            .input = "+000123",
            .expected = 123,
        },
        {
            .desc = "Convert integer with maximum value for int",
            .input = "2147483647",
            .expected = 2147483647,
        },
        {
            .desc = "Convert integer with minimum value for int",
            .input = "-2147483648",
            .expected = -2147483648,
        },
        {
            .desc = "Convert integer with overflow value",
            .input = "2147483648",
            .expected = -2147483648,
        },
        {
            .desc = "Convert integer with underflow value",
            .input = "-2147483649",
            .expected = 2147483647,
        },
        {
            .desc = "Convert integer with only negative sign",
            .input = "-",
            .expected = 0,
        },
        {
            .desc = "Convert integer with only plus sign",
            .input = "+",
            .expected = 0,
        },
        {
            .desc = "Convert empty string",
            .input = "",
            .expected = 0,
        },
        {
            .desc = "Convert string with only spaces",
            .input = "   ",
            .expected = 0,
        },
        {
            .desc = "Convert string with spaces between digits",
            .input = "12 34",
            .expected = 12,
        },
        {
            .desc = "Convert string with mixed spaces and signs",
            .input = "   +12 34",
            .expected = 12,
        },
        {
            .desc = "Convert string with non-numeric prefix",
            .input = "abc123",
            .expected = 0,
        },
        {
            .desc = "Convert string with non-numeric prefix and sign",
            .input = "+abc123",
            .expected = 0,
        },
        {
            .desc = "Convert string with non-numeric suffix and sign",
            .input = "123abc+",
            .expected = 123,
        },
        {
            .desc = "Convert string with leading whitespaces, sign and zero",
            .input = "   - 0000",
            .expected = 0,
        },
        {
            .desc = "Convert string with multiple signs",
            .input = "--123",
            .expected = 123,
        },
        {
            .desc = "Convert string with multiple signs",
            .input = "++123",
            .expected = 123,
        },
        {
            .desc = "Convert string with invalid signs",
            .input = "+-123",
            .expected = -123,
        },
        {
            .desc = "Convert string with out of range chars",
            .input = "1 2 3 4 5 6 7 8 9 0 a b c d e f g h i j k l m n o p q r s t u v w x y z",
            .expected = 1,
        },
	{
	    .desc = "Test case moulinette",
	    .input = "   ---++-123841-++1239++--1239++--",
	    .expected = 123841,
	},
	{
	    .desc = "Test case moulinette 2",
	    .input = "++--+--+--1233456-",
	    .expected = 1233456,
	}
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
        int result = ft_atoi(tests[i].input);

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
