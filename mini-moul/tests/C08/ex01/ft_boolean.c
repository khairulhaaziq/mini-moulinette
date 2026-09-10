// ALLOWED_FUNCTIONS: 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include "../../../utils/constants.h"

/* the subject's example program has its own main(), so write it out and
 * compile it against the student's header instead of #include-ing it */

static void write_fixture(void)
{
	FILE *fp;

	fp = fopen("moul_boolean_main.c", "w");
	fprintf(fp,
		"#include \"ft_boolean.h\"\n"
		"\n"
		"void ft_putstr(char *str)\n"
		"{\n"
		"	while (*str)\n"
		"		write(1, str++, 1);\n"
		"}\n"
		"\n"
		"t_bool ft_is_even(int nbr)\n"
		"{\n"
		"	return ((EVEN(nbr)) ? TRUE : FALSE);\n"
		"}\n"
		"\n"
		"int main(int argc, char **argv)\n"
		"{\n"
		"	(void)argv;\n"
		"	if (ft_is_even(argc - 1) == TRUE)\n"
		"		ft_putstr(EVEN_MSG);\n"
		"	else\n"
		"		ft_putstr(ODD_MSG);\n"
		"	return (SUCCESS);\n"
		"}\n");
	fclose(fp);
}

int test1(void);

int main(void)
{
	if (test1() != 0)
		return (-1);
	return (0);
}

int test1(void)
{
	int ok;
	FILE *fp;
	char buffer[256];
	int status;

	write_fixture();
	ok = 1;
	if (system("cc -std=gnu99 -I ../ex01 moul_boolean_main.c -o moul_boolean_main 2> /dev/null") != 0)
	{
		printf("    " RED "[1] a program including ft_boolean.h did not compile\n" DEFAULT);
		remove("moul_boolean_main.c");
		return (-1);
	}

	fp = popen("./moul_boolean_main a b", "r");
	buffer[0] = '\0';
	if (fgets(buffer, sizeof(buffer), fp))
		;
	status = WEXITSTATUS(pclose(fp));
	if (strcmp(buffer, "I have an even number of arguments.\n") != 0 || status != 0)
	{
		printf("    " RED "[1] with 2 extra arguments, expected \"I have an even number of arguments.\\n\" and exit 0, got \"%s\" (exit %d)\n" DEFAULT, buffer, status);
		ok = 0;
	}
	else
		printf("  " GREEN CHECKMARK GREY " [1] with 2 extra arguments, printed the even message\n" DEFAULT);

	fp = popen("./moul_boolean_main a", "r");
	buffer[0] = '\0';
	if (fgets(buffer, sizeof(buffer), fp))
		;
	status = WEXITSTATUS(pclose(fp));
	if (strcmp(buffer, "I have an odd number of arguments.\n") != 0 || status != 0)
	{
		printf("    " RED "[2] with 1 extra argument, expected \"I have an odd number of arguments.\\n\" and exit 0, got \"%s\" (exit %d)\n" DEFAULT, buffer, status);
		ok = 0;
	}
	else
		printf("  " GREEN CHECKMARK GREY " [2] with 1 extra argument, printed the odd message\n" DEFAULT);

	fp = popen("./moul_boolean_main", "r");
	buffer[0] = '\0';
	if (fgets(buffer, sizeof(buffer), fp))
		;
	status = WEXITSTATUS(pclose(fp));
	if (strcmp(buffer, "I have an even number of arguments.\n") != 0 || status != 0)
	{
		printf("    " RED "[3] with no extra argument, expected \"I have an even number of arguments.\\n\" and exit 0, got \"%s\" (exit %d)\n" DEFAULT, buffer, status);
		ok = 0;
	}
	else
		printf("  " GREEN CHECKMARK GREY " [3] with no extra argument, printed the even message\n" DEFAULT);

	remove("moul_boolean_main.c");
	remove("moul_boolean_main");
	return (ok ? 0 : -1);
}
