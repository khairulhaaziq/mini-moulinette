// ALLOWED_FUNCTIONS: close, open, read, write, malloc, free, strerror, basename
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

	if (system("make -C ../ex02 > /dev/null 2>&1") != 0)
	{
		printf("    " RED "[0] make did not build ft_tail\n" DEFAULT);
		return (-1);
	}
	if (test1() != 0)
		error -= 1;
	if (test2() != 0)
		error -= 1;
	if (test3() != 0)
		error -= 1;
	system("make -C ../ex02 fclean > /dev/null 2>&1");
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

static void write_fixture(char *content)
{
	FILE *fp;

	fp = fopen("moul_tail_input.txt", "w");
	fprintf(fp, "%s", content);
	fclose(fp);
}

int test1(void)
{
	char buffer[256];
	int ok;

	write_fixture("abcdefghijklmnopqrstuvwxyz");
	read_command("../ex02/ft_tail -c 5 moul_tail_input.txt 2> /dev/null", buffer, sizeof(buffer));
	ok = (strcmp(buffer, "vwxyz") == 0);
	if (!ok)
		printf("    " RED "[1] ft_tail -c 5 <file> Expected \"vwxyz\", got \"%s\"\n" DEFAULT, buffer);
	else
		printf("  " GREEN CHECKMARK GREY " [1] ft_tail -c 5 <file> printed the last 5 bytes\n" DEFAULT);
	remove("moul_tail_input.txt");
	return (ok ? 0 : -1);
}

int test2(void)
{
	char buffer[256];
	int ok;

	write_fixture("short");
	read_command("../ex02/ft_tail -c 100 moul_tail_input.txt 2> /dev/null", buffer, sizeof(buffer));
	ok = (strcmp(buffer, "short") == 0);
	if (!ok)
		printf("    " RED "[2] ft_tail -c <bigger than file> Expected the whole file \"short\", got \"%s\"\n" DEFAULT, buffer);
	else
		printf("  " GREEN CHECKMARK GREY " [2] ft_tail -c <bigger than file> printed the whole file\n" DEFAULT);
	remove("moul_tail_input.txt");
	return (ok ? 0 : -1);
}

int test3(void)
{
	char buffer[256];
	int ok;

	write_fixture("0123456789");
	read_command("../ex02/ft_tail -c 0 moul_tail_input.txt 2> /dev/null", buffer, sizeof(buffer));
	ok = (strcmp(buffer, "") == 0);
	if (!ok)
		printf("    " RED "[3] ft_tail -c 0 <file> Expected no output, got \"%s\"\n" DEFAULT, buffer);
	else
		printf("  " GREEN CHECKMARK GREY " [3] ft_tail -c 0 <file> printed nothing\n" DEFAULT);
	remove("moul_tail_input.txt");
	return (ok ? 0 : -1);
}
