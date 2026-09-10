// ALLOWED_FUNCTIONS: write
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "../../../../ex05/ft_print_comb.c"
#include "../../../utils/constants.h"

void print_success(char *str, int num);
void print_error(char *str, int num);
void redirect_output(void);
int test1(void);

int main(void)
{
        if (test1() != 0)
                return (-1);
        return (0);
}

int test1(void)
{
        redirect_output();
        // Open the output file and check its contents
        FILE *fp = fopen("output.txt", "r");
        char buffer[1024];
        fgets(buffer, sizeof(buffer), fp);
        fclose(fp);

        // Check that the output matches the expected value
        const char *expected_output = "012, 013, 014, 015, 016, 017, 018, 019, 023, 024, 025, 026, 027, 028, 029, 034, 035, 036, 037, 038, 039, 045, 046, 047, 048, 049, 056, 057, 058, 059, 067, 068, 069, 078, 079, 089, 123, 124, 125, 126, 127, 128, 129, 134, 135, 136, 137, 138, 139, 145, 146, 147, 148, 149, 156, 157, 158, 159, 167, 168, 169, 178, 179, 189, 234, 235, 236, 237, 238, 239, 245, 246, 247, 248, 249, 256, 257, 258, 259, 267, 268, 269, 278, 279, 289, 345, 346, 347, 348, 349, 356, 357, 358, 359, 367, 368, 369, 378, 379, 389, 456, 457, 458, 459, 467, 468, 469, 478, 479, 489, 567, 568, 569, 578, 579, 589, 678, 679, 689, 789";
        if (strcmp(buffer, expected_output) != 0)
        {
                printf("    " RED "[1] ft_print_comb() Expected \"%s\", got \"%s\"\n"DEFAULT, expected_output, buffer);
                remove("output.txt");
                return (-1);
        }
        else
                printf("  " GREEN CHECKMARK GREY " [1] ft_print_comb() Expected \"%s\", got \"%s\"\n"DEFAULT, expected_output, buffer);
        remove("output.txt");
        return (0);
}

void redirect_output(void)
{
         // Redirect the output to a file
        int saved_stdout = dup(STDOUT_FILENO);
        int output_fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        dup2(output_fd, STDOUT_FILENO);
        close(output_fd);

        // Call the function to be tested
        ft_print_comb();

        // Restore the original output
        fflush(stdout);
        dup2(saved_stdout, STDOUT_FILENO);
        close(saved_stdout);
}

void print_success(char *str, int num)
{
        printf("  " GREEN CHECKMARK GREY " [%d] %s\n" DEFAULT, num, str);
}

void print_error(char *str, int num)
{
        printf("    " RED "[%d] %s\n" DEFAULT, num, str);
}