#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../../../../ex08/ft_ten_queens_puzzle.c"
#include "../../../utils/constants.h"

typedef struct s_test
{
    char *desc;
    int expected_return;
    int expected_lines;
} t_test;

int run_tests(t_test *tests, int count);
int count_output_lines(void);

int main(void)
{
    t_test tests[] = {
        {
            .desc = "Ten queens puzzle should return 724 solutions",
            .expected_return = 724,
            .expected_lines = 724,
        },
    };
    int count = sizeof(tests) / sizeof(tests[0]);

    return run_tests(tests, count);
}

int count_output_lines(void)
{
    int pipefd[2];
    pid_t pid;
    int status;
    int line_count = 0;
    char buffer[1024];
    int bytes_read;
    int i;

    if (pipe(pipefd) == -1)
        return -1;

    pid = fork();
    if (pid == -1)
        return -1;

    if (pid == 0)
    {
        // Child process
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        
        ft_ten_queens_puzzle();
        exit(0);
    }
    else
    {
        // Parent process
        close(pipefd[1]);
        
        while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0)
        {
            buffer[bytes_read] = '\0';
            for (i = 0; i < bytes_read; i++)
            {
                if (buffer[i] == '\n')
                    line_count++;
            }
        }
        
        close(pipefd[0]);
        waitpid(pid, &status, 0);
    }

    return line_count;
}

int run_tests(t_test *tests, int count)
{
    int i;
    int error = 0;

    for (i = 0; i < count; i++)
    {
        int result = ft_ten_queens_puzzle();
        int output_lines = count_output_lines();

        if (result != tests[i].expected_return)
        {
            printf("    " RED "[%d] %s - Return value: Expected %d, got %d\n", i + 1, tests[i].desc, tests[i].expected_return, result);
            error -= 1;
        }
        else if (output_lines != tests[i].expected_lines)
        {
            printf("    " RED "[%d] %s - Output lines: Expected %d, got %d\n", i + 1, tests[i].desc, tests[i].expected_lines, output_lines);
            error -= 1;
        }
        else
        {
            printf("  " GREEN CHECKMARK GREY " [%d] %s - Return: %d, Lines: %d\n" DEFAULT, i + 1, tests[i].desc, result, output_lines);
        }
    }

    return error;
}