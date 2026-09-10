// ALLOWED_FUNCTIONS: write
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "../../../../ex01/ft_putstr.c"
#include "../../../utils/constants.h"

typedef struct s_test
{
        char *desc;
        char *str;
        char *expected;
} t_test;

int run_tests(t_test *tests, int count);

int main(void)
{
        t_test tests[] = {
            {
                .desc = "Output a simple string",
                .str = "hello world",
                .expected = "hello world",
            },
            {
                .desc = "Output an empty string",
                .str = "",
                .expected = "",
            },
            {
                .desc = "Output a string containing numbers",
                .str = "1234567890",
                .expected = "1234567890",
            },
            {
                .desc = "Output a string containing special characters",
                .str = "!@#$%^&*()_+}{:\"?><,./';][=-`~",
                .expected = "!@#$%^&*()_+}{:\"?><,./';][=-`~",
            },
            {
                .desc = "Output a long string",
                .str = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed non risus. Suspendisse lectus tortor, dignissim sit amet, adipiscing nec, ultricies sed, dolor. Cras elementum ultrices diam. Maecenas ligula massa, varius a, semper congue, euismod non, mi.",
                .expected = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed non risus. Suspendisse lectus tortor, dignissim sit amet, adipiscing nec, ultricies sed, dolor. Cras elementum ultrices diam. Maecenas ligula massa, varius a, semper congue, euismod non, mi.",
            }};
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
                ft_putstr(tests[i].str);

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
                {
                        printf("  " GREEN CHECKMARK GREY " [%d] %s output \"%s\" as expected\n" DEFAULT, i + 1, tests[i].desc, buffer);
                }
        }
        return (error);
}