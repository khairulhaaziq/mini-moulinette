// ALLOWED_FUNCTIONS: write
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "../../../../ex08/ft_ten_queens_puzzle.c"
#include "../../../utils/constants.h"

int test1(void);

int main(void)
{
	if (test1() != 0)
		return (-1);
	return (0);
}

static int moul_is_valid_solution(char *line)
{
	int rows[10];
	int i;
	int j;

	if ((int)strlen(line) != 10)
		return (0);
	i = 0;
	while (i < 10)
	{
		if (line[i] < '0' || line[i] > '9')
			return (0);
		rows[i] = line[i] - '0';
		i++;
	}
	i = 0;
	while (i < 10)
	{
		j = i + 1;
		while (j < 10)
		{
			if (rows[i] == rows[j])
				return (0);
			if ((rows[i] - rows[j] == j - i) || (rows[j] - rows[i] == j - i))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int test1(void)
{
	int saved_stdout;
	int output_fd;
	int result;
	FILE *fp;
	char lines[800][32];
	int line_count;
	int i;
	int j;
	int failed;

	fflush(stdout);
	saved_stdout = dup(STDOUT_FILENO);
	output_fd = open("output_c05_ex08.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	dup2(output_fd, STDOUT_FILENO);
	close(output_fd);

	result = ft_ten_queens_puzzle();

	fflush(stdout);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);

	fp = fopen("output_c05_ex08.txt", "r");
	line_count = 0;
	while (line_count < 800 && fgets(lines[line_count], sizeof(lines[0]), fp))
	{
		size_t len = strlen(lines[line_count]);

		if (len > 0 && lines[line_count][len - 1] == '\n')
			lines[line_count][len - 1] = '\0';
		line_count++;
	}
	fclose(fp);
	remove("output_c05_ex08.txt");

	failed = 0;

	if (result != 724)
	{
		printf("    " RED "[1] ft_ten_queens_puzzle() Expected return value 724, got %d\n" DEFAULT, result);
		failed = 1;
	}
	else
		printf("  " GREEN CHECKMARK GREY " [1] ft_ten_queens_puzzle() returned 724 as expected\n" DEFAULT);

	if (line_count != 724)
	{
		printf("    " RED "[2] ft_ten_queens_puzzle() Expected 724 printed solutions, got %d\n" DEFAULT, line_count);
		failed = 1;
	}
	else
		printf("  " GREEN CHECKMARK GREY " [2] ft_ten_queens_puzzle() printed 724 lines as expected\n" DEFAULT);

	i = 0;
	while (i < line_count)
	{
		if (!moul_is_valid_solution(lines[i]))
		{
			printf("    " RED "[3] ft_ten_queens_puzzle() solution \"%s\" is not a valid non-attacking placement\n" DEFAULT, lines[i]);
			failed = 1;
			break;
		}
		i++;
	}
	if (i == line_count && line_count > 0)
		printf("  " GREEN CHECKMARK GREY " [3] All printed solutions are valid non-attacking placements\n" DEFAULT);

	i = 0;
	while (i < line_count)
	{
		j = i + 1;
		while (j < line_count)
		{
			if (strcmp(lines[i], lines[j]) == 0)
			{
				printf("    " RED "[4] ft_ten_queens_puzzle() duplicate solution \"%s\"\n" DEFAULT, lines[i]);
				failed = 1;
			}
			j++;
		}
		i++;
	}
	if (line_count > 0 && !failed)
		printf("  " GREEN CHECKMARK GREY " [4] All printed solutions are unique\n" DEFAULT);

	if (failed)
		return (-1);
	return (0);
}
