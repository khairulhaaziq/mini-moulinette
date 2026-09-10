// ALLOWED_FUNCTIONS: write
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../../../utils/constants.h"

/* no fixed file name here, so build libft.a with the student's own
 * script, then link a small harness against it, like C06's argv tests */

int test1(void);

int main(void)
{
	if (test1() != 0)
		return (-1);
	return (0);
}

static int build_lib(void)
{
	return (system("(cd ../ex00 && sh libft_creator.sh) > /dev/null 2>&1") == 0
		&& access("../ex00/libft.a", F_OK) == 0);
}

static int write_harness(void)
{
	FILE *fp;

	fp = fopen("moul_harness.c", "w");
	if (!fp)
		return (0);
	fprintf(fp,
		"#include <stdio.h>\n"
		"extern void ft_putchar(char c);\n"
		"extern void ft_swap(int *a, int *b);\n"
		"extern void ft_putstr(char *str);\n"
		"extern int ft_strlen(char *str);\n"
		"extern int ft_strcmp(char *s1, char *s2);\n"
		"int main(void)\n"
		"{\n"
		"	int a = 1;\n"
		"	int b = 2;\n"
		"\n"
		"	ft_putchar('A');\n"
		"	ft_putstr(\"Hello\");\n"
		"	printf(\"|%%d|\", ft_strlen(\"Hello, World!\"));\n"
		"	printf(\"%%d|\", ft_strcmp(\"abc\", \"abc\"));\n"
		"	printf(\"%%d|\", ft_strcmp(\"abc\", \"abd\") < 0 ? -1 : 1);\n"
		"	ft_swap(&a, &b);\n"
		"	printf(\"%%d,%%d\\n\", a, b);\n"
		"	return (0);\n"
		"}\n");
	fclose(fp);
	return (1);
}

int test1(void)
{
	FILE *fp;
	char buffer[256];
	int ok;

	ok = 1;
	if (!build_lib())
	{
		printf("    " RED "[1] libft_creator.sh did not produce ../ex00/libft.a\n" DEFAULT);
		system("rm -f ../ex00/libft.a ../ex00/*.o 2> /dev/null");
		return (-1);
	}
	if (!write_harness() || system("cc -std=gnu99 moul_harness.c ../ex00/libft.a -o moul_harness 2> /dev/null") != 0)
	{
		printf("    " RED "[2] a program linked against libft.a did not compile\n" DEFAULT);
		remove("moul_harness.c");
		system("rm -f ../ex00/libft.a ../ex00/*.o 2> /dev/null");
		return (-1);
	}

	fp = popen("./moul_harness", "r");
	buffer[0] = '\0';
	if (fp)
	{
		if (!fgets(buffer, sizeof(buffer), fp))
			buffer[0] = '\0';
		pclose(fp);
	}
	remove("moul_harness.c");
	remove("moul_harness");
	system("rm -f ../ex00/libft.a ../ex00/*.o 2> /dev/null");

	if (strcmp(buffer, "AHello|13|0|-1|2,1\n") != 0)
	{
		printf("    " RED "[1] libft functions did not behave as expected, got \"%s\"\n" DEFAULT, buffer);
		ok = 0;
	}
	else
		printf("  " GREEN CHECKMARK GREY " [1] ft_putchar, ft_putstr, ft_strlen, ft_strcmp and ft_swap all behaved as expected\n" DEFAULT);
	return (ok ? 0 : -1);
}
