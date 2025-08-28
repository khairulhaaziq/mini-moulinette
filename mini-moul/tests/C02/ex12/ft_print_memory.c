#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <regex.h>
#include "../../../../ex12/ft_print_memory.c"
#include "../../../utils/constants.h"

typedef struct s_test
{
	char *desc;
	char *data;
	unsigned int size;
	int should_have_output;
} t_test;

int run_tests(t_test *tests, int count);

int main(void)
{
	t_test tests[] = {
		{
			.desc = "ft_print_memory with size 0",
			.data = "Hello",
			.size = 0,
			.should_have_output = 0
		},
		{
			.desc = "ft_print_memory with 1 character",
			.data = "A",
			.size = 1,
			.should_have_output = 1
		},
		{
			.desc = "ft_print_memory with 8 characters",
			.data = "Bonjour!",
			.size = 8,
			.should_have_output = 1
		},
		{
			.desc = "ft_print_memory with exactly 16 characters",
			.data = "0123456789ABCDEF",
			.size = 16,
			.should_have_output = 1
		},
		{
			.desc = "ft_print_memory with 33 characters (multiple lines)",
			.data = "Bonjour les amis, comment ca va?!",
			.size = 33,
			.should_have_output = 1
		},
		{
			.desc = "ft_print_memory with non-printable characters",
			.data = "Hello\tWorld\n\x01\x02",
			.size = 13,
			.should_have_output = 1
		}
	};
	int count = sizeof(tests) / sizeof(tests[0]);

	return (run_tests(tests, count));
}

int validate_line_format(char *line)
{
	regex_t regex;
	int ret;

	// Pattern: 16 hex digits + colon + space + hex content + space + printable chars
	char *pattern = "^[0-9a-fA-F]{16}: ([0-9a-fA-F]{2}){1,16}.*";
	
	ret = regcomp(&regex, pattern, REG_EXTENDED);
	if (ret)
		return 0;

	ret = regexec(&regex, line, 0, NULL, 0);
	regfree(&regex);

	return (ret == 0) ? 1 : 0;
}

int run_tests(t_test *tests, int count)
{
	int i;
	int error = 0;

	for (i = 0; i < count; i++)
	{
		// Flush the standard output buffer
		fflush(stdout);

		char buffer[4096];
		memset(buffer, 0, sizeof(buffer));

		// Redirect the output to a file
		int saved_stdout = dup(STDOUT_FILENO);
		int output_fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		dup2(output_fd, STDOUT_FILENO);
		close(output_fd);

		// Call the function to be tested
		void *result = ft_print_memory(tests[i].data, tests[i].size);

		// Restore the original output
		fflush(stdout);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);

		// Check return value
		if (result != tests[i].data)
		{
			printf("    " RED "[%d] %s Function should return input address\n", i + 1, tests[i].desc);
			error -= 1;
			remove("output.txt");
			continue;
		}

		// Read the output file
		FILE *fp = fopen("output.txt", "r");
		if (fp)
		{
			fread(buffer, 1, sizeof(buffer) - 1, fp);
			fclose(fp);
		}

		// Test size 0 case
		if (tests[i].size == 0)
		{
			if (strlen(buffer) == 0)
				printf("  " GREEN CHECKMARK GREY " [%d] %s No output for size 0\n" DEFAULT, i + 1, tests[i].desc);
			else
			{
				printf("    " RED "[%d] %s Expected no output for size 0\n", i + 1, tests[i].desc);
				error -= 1;
			}
		}
		else
		{
			// Check if we have output
			if (strlen(buffer) == 0)
			{
				printf("    " RED "[%d] %s Expected output but got none\n", i + 1, tests[i].desc);
				error -= 1;
			}
			else
			{
				// Validate each line format
				char *line = strtok(buffer, "\n");
				int format_ok = 1;
				int line_count = 0;

				while (line && format_ok)
				{
					line_count++;
					if (!validate_line_format(line))
						format_ok = 0;
					line = strtok(NULL, "\n");
				}

				// Check expected number of lines
				int expected_lines = (tests[i].size + 15) / 16;
				
				if (format_ok && line_count == expected_lines)
					printf("  " GREEN CHECKMARK GREY " [%d] %s Format validation passed (%d lines)\n" DEFAULT, i + 1, tests[i].desc, line_count);
				else
				{
					printf("    " RED "[%d] %s Format validation failed (expected %d lines, got %d)\n", i + 1, tests[i].desc, expected_lines, line_count);
					error -= 1;
				}
			}
		}

		// Delete the output file
		remove("output.txt");
	}

	return (error);
}