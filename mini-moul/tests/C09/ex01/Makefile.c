// ALLOWED_FUNCTIONS: 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "../../../utils/constants.h"

/* subject says the grader supplies srcs/ and includes/ft.h itself, so
 * drop that fixture in before driving make - but some students commit
 * their own srcs/, includes/ or libft.a anyway (to keep a working local
 * copy), so back those aside first instead of silently clobbering and
 * later deleting the student's own files */

int test1(void);

static void backup_existing(void)
{
	system("mv ../ex01/srcs ../ex01/moul_srcs_backup 2> /dev/null");
	system("mv ../ex01/includes ../ex01/moul_includes_backup 2> /dev/null");
	system("mv ../ex01/libft.a ../ex01/moul_libft_backup.a 2> /dev/null");
}

static void restore_backup(void)
{
	system("mv ../ex01/moul_srcs_backup ../ex01/srcs 2> /dev/null");
	system("mv ../ex01/moul_includes_backup ../ex01/includes 2> /dev/null");
	system("mv ../ex01/moul_libft_backup.a ../ex01/libft.a 2> /dev/null");
}

static void write_fixture(void)
{
	FILE *fp;

	backup_existing();
	system("mkdir -p ../ex01/srcs ../ex01/includes");
	fp = fopen("../ex01/includes/ft.h", "w");
	fprintf(fp,
		"#ifndef FT_H\n# define FT_H\n"
		"void ft_putchar(char c);\n"
		"void ft_swap(int *a, int *b);\n"
		"void ft_putstr(char *str);\n"
		"int ft_strlen(char *str);\n"
		"int ft_strcmp(char *s1, char *s2);\n"
		"#endif\n");
	fclose(fp);
	fp = fopen("../ex01/srcs/ft_putchar.c", "w");
	fprintf(fp, "#include <unistd.h>\n#include \"../includes/ft.h\"\nvoid ft_putchar(char c) { write(1, &c, 1); }\n");
	fclose(fp);
	fp = fopen("../ex01/srcs/ft_swap.c", "w");
	fprintf(fp, "#include \"../includes/ft.h\"\nvoid ft_swap(int *a, int *b) { int t = *a; *a = *b; *b = t; }\n");
	fclose(fp);
	fp = fopen("../ex01/srcs/ft_putstr.c", "w");
	fprintf(fp, "#include <unistd.h>\n#include \"../includes/ft.h\"\nvoid ft_putstr(char *str) { while (*str) write(1, str++, 1); }\n");
	fclose(fp);
	fp = fopen("../ex01/srcs/ft_strlen.c", "w");
	fprintf(fp, "#include \"../includes/ft.h\"\nint ft_strlen(char *str) { int n = 0; while (str[n]) n++; return (n); }\n");
	fclose(fp);
	fp = fopen("../ex01/srcs/ft_strcmp.c", "w");
	fprintf(fp,
		"#include \"../includes/ft.h\"\n"
		"int ft_strcmp(char *s1, char *s2)\n"
		"{\n"
		"	while (*s1 && *s1 == *s2) { s1++; s2++; }\n"
		"	return ((unsigned char)*s1 - (unsigned char)*s2);\n"
		"}\n");
	fclose(fp);
}

static void remove_fixture(void)
{
	system("rm -rf ../ex01/srcs ../ex01/includes ../ex01/libft.a ../ex01/*.o 2> /dev/null");
	restore_backup();
}

static int file_exists(char *path)
{
	struct stat st;

	return (stat(path, &st) == 0);
}

int main(void)
{
	if (test1() != 0)
		return (-1);
	return (0);
}

int test1(void)
{
	int ok;

	write_fixture();
	ok = 1;

	if (system("make -C ../ex01 > /dev/null 2>&1") != 0 || !file_exists("../ex01/libft.a"))
	{
		printf("    " RED "[1] make (or make all) did not produce libft.a at the root of the exercise\n" DEFAULT);
		ok = 0;
	}
	else
		printf("  " GREEN CHECKMARK GREY " [1] make produced libft.a at the root of the exercise\n" DEFAULT);

	if (ok && !file_exists("../ex01/srcs/ft_putchar.o"))
	{
		printf("    " RED "[2] .o files were not placed next to their .c file in srcs/\n" DEFAULT);
		ok = 0;
	}
	else if (ok)
		printf("  " GREEN CHECKMARK GREY " [2] .o files were placed next to their .c file in srcs/\n" DEFAULT);

	if (ok)
	{
		system("make -C ../ex01 clean > /dev/null 2>&1");
		if (file_exists("../ex01/srcs/ft_putchar.o"))
		{
			printf("    " RED "[3] make clean did not remove the .o files\n" DEFAULT);
			ok = 0;
		}
		else if (!file_exists("../ex01/libft.a"))
		{
			printf("    " RED "[3] make clean should not remove libft.a\n" DEFAULT);
			ok = 0;
		}
		else
			printf("  " GREEN CHECKMARK GREY " [3] make clean removed the .o files and kept libft.a\n" DEFAULT);
	}

	if (ok)
	{
		system("make -C ../ex01 fclean > /dev/null 2>&1");
		if (file_exists("../ex01/libft.a"))
		{
			printf("    " RED "[4] make fclean did not remove libft.a\n" DEFAULT);
			ok = 0;
		}
		else
			printf("  " GREEN CHECKMARK GREY " [4] make fclean removed libft.a\n" DEFAULT);
	}

	if (ok && (system("make -C ../ex01 re > /dev/null 2>&1") != 0 || !file_exists("../ex01/libft.a")))
	{
		printf("    " RED "[5] make re did not rebuild libft.a\n" DEFAULT);
		ok = 0;
	}
	else if (ok)
		printf("  " GREEN CHECKMARK GREY " [5] make re rebuilt libft.a\n" DEFAULT);

	remove_fixture();
	return (ok ? 0 : -1);
}
