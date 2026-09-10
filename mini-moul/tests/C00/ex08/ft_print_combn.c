// ALLOWED_FUNCTIONS: write
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "../../../../ex08/ft_print_combn.c"
#include "../../../utils/constants.h"

typedef struct s_test
{
        char *desc;
        int n;
        char *expected;
} t_test;

int run_tests(t_test *tests, int count);

int main(void)
{
        t_test tests[] = {
            {.desc = "ft_print_combn(2)",
             .n = 2,
             .expected = "01, 02, 03, 04, 05, 06, 07, 08, 09, 12, 13, 14, 15, 16, 17, 18, 19, 23, 24, 25, 26, 27, 28, 29, 34, 35, 36, 37, 38, 39, 45, 46, 47, 48, 49, 56, 57, 58, 59, 67, 68, 69, 78, 79, 89"},
             {.desc = "ft_print_combn(3)",
             .n = 3,
             .expected = "012, 013, 014, 015, 016, 017, 018, 019, 023, 024, 025, 026, 027, 028, 029, 034, 035, 036, 037, 038, 039, 045, 046, 047, 048, 049, 056, 057, 058, 059, 067, 068, 069, 078, 079, 089, 123, 124, 125, 126, 127, 128, 129, 134, 135, 136, 137, 138, 139, 145, 146, 147, 148, 149, 156, 157, 158, 159, 167, 168, 169, 178, 179, 189, 234, 235, 236, 237, 238, 239, 245, 246, 247, 248, 249, 256, 257, 258, 259, 267, 268, 269, 278, 279, 289, 345, 346, 347, 348, 349, 356, 357, 358, 359, 367, 368, 369, 378, 379, 389, 456, 457, 458, 459, 467, 468, 469, 478, 479, 489, 567, 568, 569, 578, 579, 589, 678, 679, 689, 789"},
            // Add more test cases here
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
                // Flush the standard output buffer
                fflush(stdout);

                char buffer[10240];
                // Clear the buffer used to capture the output of the function being tested
                memset(buffer, 0, sizeof(buffer));

                // Redirect the output to a file
                int saved_stdout = dup(STDOUT_FILENO);
                int output_fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
                dup2(output_fd, STDOUT_FILENO);
                close(output_fd);

                // Call the function to be tested
                ft_print_combn(tests[i].n);

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
