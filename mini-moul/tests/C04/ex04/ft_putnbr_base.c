#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "../../../../ex04/ft_putnbr_base.c"
#include "../../../utils/constants.h"

typedef struct s_test
{
    char *desc;
    int nbr;
    char *base;
    char *expected;
} t_test;

int run_tests(t_test *tests, int count);

int main(void)
{
    t_test tests[] = {
    {
        .desc = "Convert a negative decimal number to binary",
        .nbr = -12,
        .base = "01",
        .expected = "-1100",
    },
    {
        .desc = "Convert a decimal number to custom base",
        .nbr = 40,
        .base = "poneyvif",
        .expected = "vp",
    },
    {
        .desc = "Convert a decimal number to decimal",
        .nbr = 894867,
        .base = "0123456789",
        .expected = "894867",
    },
    {
        .desc = "Convert a decimal number to hexadecimal",
        .nbr = 53,
        .base = "0123456789abcdef",
        .expected = "35",
    },
    {
        .desc = "Convert zero to binary",
        .nbr = 0,
        .base = "01",
        .expected = "0",
    },
    {
        .desc = "Empty base string",
        .nbr = 123,
        .base = "",
        .expected = "",
    },
    {
        .desc = "Invalid base string with duplicate characters",
        .nbr = 123,
        .base = "abccde",
        .expected = "",
    },
    {
        .desc = "Smallest possible negative value",
        .nbr = -2147483648,
        .base = "01",
        .expected = "-10000000000000000000000000000000",
    },
    {
        .desc = "Largest possible positive value",
        .nbr = 2147483647,
        .base = "0123456789abcdef",
        .expected = "7fffffff",
    },
    {
        .desc = "Base string with one character",
        .nbr = 123,
        .base = "a",
        .expected = "",
    },
    {
	.desc = "Zero with empty base",
	.nbr = 0,
	.base = "",
	.expected = "",
    },
    {
	.desc = "Positive number with single-character base",
	.nbr = 42,
	.base = "a",
	.expected = "",
    },
    {
	.desc = "Negative number with base containing +",
	.nbr = -10,
	.base = "0+1",
	.expected = "",
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
        // Flush the standard output buffer
        fflush(stdout);

        char buffer[1024];
        // Clear the buffer used to capture the output of the function being tested
        memset(buffer, 0, sizeof(buffer));

        // Redirect the output to a file
        int saved_stdout = dup(STDOUT_FILENO);
        int output_fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        dup2(output_fd, STDOUT_FILENO);
        close(output_fd);

        // Call the function to be tested
        ft_putnbr_base(tests[i].nbr, tests[i].base);

        // Restore the original output
        fflush(stdout);
        dup2(saved_stdout, STDOUT_FILENO);
        close(saved_stdout);

        // Open the output file and check its contents
        FILE *fp = fopen("output.txt", "r");
        fgets(buffer, sizeof(buffer), fp);
        fclose(fp);

        // Check that the output matches the expected value
        if (strcmp(buffer, tests[i].expected) != 0)
        {
            printf("    " RED "[%d] %s Expected \"%s\", got \"%s\"\n", i + 1, tests[i].desc, tests[i].expected, buffer);
            error -= 1;
        }
        else
            printf("  " GREEN CHECKMARK GREY " [%d] %s output \"%s\" as expected\n" DEFAULT, i + 1, tests[i].desc, buffer);

        // Delete the output file
        remove("output.txt");
    }

    return (error);
}
