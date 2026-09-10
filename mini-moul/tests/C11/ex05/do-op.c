// ALLOWED_FUNCTIONS: write
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "../../../utils/constants.h"

/* own main(), no fixed file name: build every .c in ../ex05/ into a
 * binary (like C06's argv tests) and drive it via popen */

typedef struct s_test
{
	char *desc;
	char *args;
	char *expected;
} t_test;

int run_tests(t_test *tests, int count);

int main(void)
{
	t_test tests[] = {
		{.desc = "do-op with no arguments prints nothing",
		 .args = "",
		 .expected = NULL},
		{.desc = "do-op 1 + 1",
		 .args = "'1' '+' '1'",
		 .expected = "2\n"},
		{.desc = "do-op 42amis - --+-20toto12",
		 .args = "'42amis' '-' '--+-20toto12'",
		 .expected = "62\n"},
		{.desc = "do-op 1 p 1 (invalid operator)",
		 .args = "'1' 'p' '1'",
		 .expected = "0\n"},
		{.desc = "do-op 1 + toto3",
		 .args = "'1' '+' 'toto3'",
		 .expected = "1\n"},
		{.desc = "do-op toto3 + 4",
		 .args = "'toto3' '+' '4'",
		 .expected = "4\n"},
		{.desc = "do-op foo plus bar (invalid operator)",
		 .args = "'foo' 'plus' 'bar'",
		 .expected = "0\n"},
		{.desc = "do-op 10 * 3",
		 .args = "'10' '*' '3'",
		 .expected = "30\n"},
		{.desc = "do-op 25 / 0",
		 .args = "'25' '/' '0'",
		 .expected = "Stop : division by zero\n"},
		{.desc = "do-op 25 % 0",
		 .args = "'25' '%' '0'",
		 .expected = "Stop : modulo by zero\n"},
	};
	int count = sizeof(tests) / sizeof(tests[0]);

	return (run_tests(tests, count));
}

int run_tests(t_test *tests, int count)
{
	int i;
	int error = 0;
	char run_command[1024];
	char buffer[4096];
	FILE *fp;
	size_t total_read;
	size_t bytes_read;
	int has_makefile;
	char *binary;

	/* prefer the student's own Makefile when there is one: it knows its
	 * own -I paths (e.g. headers under includes/), and the subject's
	 * own example ("./do-op 42 + 21") means `make` produces a binary
	 * literally named do-op right there */
	has_makefile = (access("../ex05/Makefile", F_OK) == 0);
	if (has_makefile)
	{
		binary = "../ex05/do-op";
		if (system("make -C ../ex05 > /dev/null 2>&1") != 0 || access(binary, F_OK) != 0)
		{
			printf("    " RED "[0] do-op did not compile\n" DEFAULT);
			return (-1);
		}
	}
	else
	{
		binary = "./do_op_bin";
		if (system("cc -Wall -Werror -Wextra ../ex05/*.c -o do_op_bin 2>/dev/null") != 0)
		{
			printf("    " RED "[0] do-op did not compile\n" DEFAULT);
			return (-1);
		}
	}

	for (i = 0; i < count; i++)
	{
		snprintf(run_command, sizeof(run_command), "%s %s 2>/dev/null", binary, tests[i].args);
		fp = popen(run_command, "r");
		if (!fp)
		{
			fprintf(stderr, "Failed to run command '%s': %s\n", run_command, strerror(errno));
			if (has_makefile)
				system("make -C ../ex05 fclean > /dev/null 2>&1");
			else
				remove("do_op_bin");
			return (-1);
		}
		total_read = 0;
		buffer[0] = '\0';
		while (total_read < sizeof(buffer) - 1 && (bytes_read = fread(buffer + total_read, 1, sizeof(buffer) - 1 - total_read, fp)) > 0)
			total_read += bytes_read;
		buffer[total_read] = '\0';
		pclose(fp);

		if (tests[i].expected == NULL)
		{
			if (total_read != 0)
			{
				printf("    " RED "[%d] %s Expected no output, got \"%s\"\n" DEFAULT, i + 1, tests[i].desc, buffer);
				error -= 1;
			}
			else
				printf("  " GREEN CHECKMARK GREY " [%d] %s produced no output as expected\n" DEFAULT, i + 1, tests[i].desc);
		}
		else if (strcmp(buffer, tests[i].expected) != 0)
		{
			printf("    " RED "[%d] %s Expected \"%s\", got \"%s\"\n" DEFAULT, i + 1, tests[i].desc, tests[i].expected, buffer);
			error -= 1;
		}
		else
			printf("  " GREEN CHECKMARK GREY " [%d] %s output \"%s\" as expected\n" DEFAULT, i + 1, tests[i].desc, buffer);
	}

	if (has_makefile)
		system("make -C ../ex05 fclean > /dev/null 2>&1");
	else
		remove("do_op_bin");
	return (error);
}
