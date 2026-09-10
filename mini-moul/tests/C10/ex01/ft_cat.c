// ALLOWED_FUNCTIONS: close, open, read, write, strerror, basename
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../utils/constants.h"

int test1(void);
int test2(void);
int test3(void);

int main(void)
{
	int error = 0;

	if (system("make -C ../ex01 > /dev/null 2>&1") != 0)
	{
		printf("    " RED "[0] make did not build ft_cat\n" DEFAULT);
		return (-1);
	}
	if (test1() != 0)
		error -= 1;
	if (test2() != 0)
		error -= 1;
	if (test3() != 0)
		error -= 1;
	system("make -C ../ex01 fclean > /dev/null 2>&1");
	return (error);
}

static void read_command(char *command, char *out, size_t out_size)
{
	FILE *fp;
	size_t n;

	fp = popen(command, "r");
	n = fread(out, 1, out_size - 1, fp);
	out[n] = '\0';
	pclose(fp);
}

int test1(void)
{
	FILE *fp;
	char buffer[256];
	int ok;

	fp = fopen("moul_cat_a.txt", "w");
	fprintf(fp, "one\ntwo\nthree");
	fclose(fp);

	read_command("../ex01/ft_cat moul_cat_a.txt 2> /dev/null", buffer, sizeof(buffer));
	ok = (strcmp(buffer, "one\ntwo\nthree") == 0);
	if (!ok)
		printf("    " RED "[1] ft_cat <file> did not print the file's content exactly, got \"%s\"\n" DEFAULT, buffer);
	else
		printf("  " GREEN CHECKMARK GREY " [1] ft_cat <file> printed the file's content exactly\n" DEFAULT);

	remove("moul_cat_a.txt");
	return (ok ? 0 : -1);
}

int test2(void)
{
	FILE *fp;
	char buffer[256];
	int ok;

	fp = fopen("moul_cat_a.txt", "w");
	fprintf(fp, "AAA\n");
	fclose(fp);
	fp = fopen("moul_cat_b.txt", "w");
	fprintf(fp, "BBB\n");
	fclose(fp);

	read_command("../ex01/ft_cat moul_cat_a.txt moul_cat_b.txt 2> /dev/null", buffer, sizeof(buffer));
	ok = (strcmp(buffer, "AAA\nBBB\n") == 0);
	if (!ok)
		printf("    " RED "[2] ft_cat <file1> <file2> did not concatenate them in order, got \"%s\"\n" DEFAULT, buffer);
	else
		printf("  " GREEN CHECKMARK GREY " [2] ft_cat <file1> <file2> concatenated them in order\n" DEFAULT);

	remove("moul_cat_a.txt");
	remove("moul_cat_b.txt");
	return (ok ? 0 : -1);
}

int test3(void)
{
	FILE *fp;
	char buffer[256];
	int ok;

	fp = fopen("moul_cat_stdin.txt", "w");
	fprintf(fp, "from stdin");
	fclose(fp);

	read_command("../ex01/ft_cat < moul_cat_stdin.txt 2> /dev/null", buffer, sizeof(buffer));
	ok = (strcmp(buffer, "from stdin") == 0);
	if (!ok)
		printf("    " RED "[3] ft_cat with no argument did not echo stdin, got \"%s\"\n" DEFAULT, buffer);
	else
		printf("  " GREEN CHECKMARK GREY " [3] ft_cat with no argument echoed stdin\n" DEFAULT);

	remove("moul_cat_stdin.txt");
	return (ok ? 0 : -1);
}
