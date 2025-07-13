#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../../ex05/ft_strlcat.c"
#include "../../../utils/constants.h"

typedef struct s_test
{
    char *desc;
    char *src;
    char *dest;
    int size;
    char *expected_output;
	unsigned int pot;
} t_test;

int run_tests(t_test *tests, int count);

int main(void)
{
    t_test tests[] = {
        {
            .desc = "Concatenate two strings",
            .src = "Born to code",
            .dest = "1337 42",
            .size = 20,
            .expected_output = "1337 42Born to code",
			.pot = 19,
        },
        {
            .desc = "Concatenate empty strings",
            .src = "",
            .dest = "",
            .size = 10,
            .expected_output = "",
			.pot = 0,
        },
        {
            .desc = "Append to an empty string",
            .src = "hello",
            .dest = "",
            .size = 10,
            .expected_output = "hello",
			.pot = 5,
        },
        {
            .desc = "Concatenate with string larger than size",
            .src = "Born to code",
            .dest = "1337 42",
            .size = 7,
            .expected_output = "1337 42",
			.pot = 19,
        },
        {
            .desc = "Concatenate same strings with size larger than sum of their lengths",
            .src = "Test",
            .dest = "Test",
            .size = 10,
            .expected_output = "TestTest",
			.pot = 8,
        },
		{
			.desc = "Something",
			.src = "and!",
			.dest = "hello world",
			.size = 5,
			.expected_output = "hello world",
			.pot = 9,
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
        char dest[strlen(tests[i].dest) + 1];
        strcpy(dest, tests[i].dest);

        unsigned int pot_len = ft_strlcat(dest, tests[i].src, tests[i].size);

        if (strcmp(dest, tests[i].expected_output) != 0 || pot_len != tests[i].pot)
        {
            printf("    " RED "[%d] %s Expected \"%s\" output \"%s\"\n" DEFAULT, i + 1, tests[i].desc, tests[i].expected_output, dest);
			printf("    " RED "[%d] %s Len Expected \"%u\" output \"%u\"\n\n" DEFAULT, i + 1, "Expected Lenth V. Output Length", tests[i].pot, pot_len);
            error -= 1;
        }
        else
        {
            printf("  " GREEN CHECKMARK GREY " [%d] %s Expected \"%s\" output \"%s\"\n" DEFAULT, i + 1, tests[i].desc, tests[i].expected_output, dest);
        }
    }

    return error;
}
