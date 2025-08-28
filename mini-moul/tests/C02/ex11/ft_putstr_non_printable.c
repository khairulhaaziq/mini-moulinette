#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "../../../../ex11/ft_putstr_non_printable.c"
#include "../../../utils/constants.h"

typedef struct s_test
{
	char *desc;
	char *src;
	char *expected;
} t_test;

int run_tests(t_test *tests, int count);

int main(void)
{
	t_test tests[] = {
	    {.desc = "ft_putstr_non_printable(\"Coucou\\ntu vas bien\")",
	     .src = "Coucou\ntu vas bien",
	     .expected = "Coucou\\0atu vas bien"},
	    {.desc = "ft_putstr_non_printable(\"\")",
	     .src = "",
	     .expected = ""},
	    {.desc = "ft_putstr_non_printable(\"\\x01\")",
	     .src = "\t01",
	     .expected = "\\0901"},
	    {.desc = "ft_putstr_non_printable(\"\\x1F\")",
	     .src = "\x1F",
	     .expected = "\\1f"},
	    {.desc = "ft_putstr_non_printable(\"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ\")",
	     .src = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ",
	     .expected = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"},
	    {.desc = "ft_putstr_non_printable(\"0123456789\")",
	     .src = "0123456789",
	     .expected = "0123456789"},
	    {.desc = "ft_putstr_non_printable(\"This is a long string. It has more than 16 bytes.\")",
	     .src = "This is a long string. It has more than 16 bytes.",
	     .expected = "This is a long string. It has more than 16 bytes."},
	    {
		.desc = "Print non-printable ASCII characters",
		.src = "Some\nrandom\ttext\x0Fwith\nnon-printable\rcharacters",
		.expected = "Some\\0arandom\\09text\\0fwith\\0anon-printable\\0dcharacters",
	    },
	    {
		.desc = "Print empty string",
		.src = "",
		.expected = "",
	    },
	    {
		.desc = "Print string with only printable characters",
		.src = "Hello, world!",
		.expected = "Hello, world!",
	    },
	    {
		.desc = "Print string with more than 16 bytes",
		.src = "This is a long string. It has more than 16 bytes.",
		.expected = "This is a long string. It has more than 16 bytes.",
	    },
	    {
		.desc = "Print string with exactly 16 bytes",
		.src = "0123456789ABCDEF",
		.expected = "0123456789ABCDEF",
	    },
	    {
		.desc = "Print DEL character (ASCII 127)",
		.src = "Hello\x7FWorld",
		.expected = "Hello\\7fWorld",
	    },
	    {
		.desc = "Print extended ASCII character (ASCII 128)",
		.src = (char[]){'T','e','s','t','\x80','E','n','d','\0'},
		.expected = "Test\\80End",
	    },
	    {
		.desc = "Print extended ASCII character (ASCII 255)",
		.src = (char[]){'T','e','s','t','\xFF','E','n','d','\0'},
		.expected = "Test\\ffEnd",
	    },
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

		char buffer[1024];
		// Clear the buffer used to capture the output of the function being tested
		memset(buffer, 0, sizeof(buffer));

		// Redirect the output to a file
		int saved_stdout = dup(STDOUT_FILENO);
		int output_fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		dup2(output_fd, STDOUT_FILENO);
		close(output_fd);

		// Call the function to be tested
		ft_putstr_non_printable(tests[i].src);

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
