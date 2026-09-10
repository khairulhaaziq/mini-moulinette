// ALLOWED_FUNCTIONS: close, open, read, write
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../utils/constants.h"

/* no fixed source file name, so build with make instead of #include-ing
 * a specific file, like C06's argv exercises */

int test1(void);
int test2(void);
int test3(void);
int test4(void);

int main(void)
{
	int error = 0;

	if (system("make -C ../ex00 > /dev/null 2>&1") != 0)
	{
		printf("    " RED "[0] make did not build ft_display_file\n" DEFAULT);
		return (-1);
	}
	if (test1() != 0)
		error -= 1;
	if (test2() != 0)
		error -= 1;
	if (test3() != 0)
		error -= 1;
	if (test4() != 0)
		error -= 1;
	system("make -C ../ex00 fclean > /dev/null 2>&1");
	return (error);
}

static int read_command(char *command, char *out, size_t out_size)
{
	FILE *fp;
	size_t n;

	fp = popen(command, "r");
	if (!fp)
		return (0);
	n = fread(out, 1, out_size - 1, fp);
	out[n] = '\0';
	pclose(fp);
	return (1);
}

int test1(void)
{
	FILE *fp;
	char stdout_buf[256];
	char stderr_buf[256];
	int ok;

	fp = fopen("moul_display_input.txt", "w");
	fprintf(fp, "Hello, mini-moulinette!\nSecond line.");
	fclose(fp);

	read_command("../ex00/ft_display_file moul_display_input.txt 2> moul_display_err.txt", stdout_buf, sizeof(stdout_buf));
	fp = fopen("moul_display_err.txt", "r");
	fgets(stderr_buf, sizeof(stderr_buf), fp);
	fclose(fp);

	ok = (strcmp(stdout_buf, "Hello, mini-moulinette!\nSecond line.") == 0);
	if (!ok)
		printf("    " RED "[1] ft_display_file <file> did not print the file's content exactly, got \"%s\"\n" DEFAULT, stdout_buf);
	else
		printf("  " GREEN CHECKMARK GREY " [1] ft_display_file <file> printed the file's content exactly\n" DEFAULT);

	remove("moul_display_input.txt");
	remove("moul_display_err.txt");
	return (ok ? 0 : -1);
}

int test2(void)
{
	/* the subject just says errors go to "their reserved output"
	 * without naming stderr outright, so accept either stream */
	char buf[256];
	int ok;

	read_command("../ex00/ft_display_file 2>&1", buf, sizeof(buf));

	ok = (strcmp(buf, "File name missing.\n") == 0);
	if (!ok)
		printf("    " RED "[2] ft_display_file with no argument Expected \"File name missing.\\n\", got \"%s\"\n" DEFAULT, buf);
	else
		printf("  " GREEN CHECKMARK GREY " [2] ft_display_file with no argument printed \"File name missing.\"\n" DEFAULT);

	return (ok ? 0 : -1);
}

int test3(void)
{
	char buf[256];
	int ok;

	read_command("../ex00/ft_display_file a b 2>&1", buf, sizeof(buf));

	ok = (strcmp(buf, "Too many arguments.\n") == 0);
	if (!ok)
		printf("    " RED "[3] ft_display_file with 2 arguments Expected \"Too many arguments.\\n\", got \"%s\"\n" DEFAULT, buf);
	else
		printf("  " GREEN CHECKMARK GREY " [3] ft_display_file with 2 arguments printed \"Too many arguments.\"\n" DEFAULT);

	return (ok ? 0 : -1);
}

int test4(void)
{
	char buf[256];
	int ok;

	read_command("../ex00/ft_display_file moul_does_not_exist.txt 2>&1", buf, sizeof(buf));

	ok = (strcmp(buf, "Cannot read file.\n") == 0);
	if (!ok)
		printf("    " RED "[4] ft_display_file on a missing file Expected \"Cannot read file.\\n\", got \"%s\"\n" DEFAULT, buf);
	else
		printf("  " GREEN CHECKMARK GREY " [4] ft_display_file on a missing file printed \"Cannot read file.\"\n" DEFAULT);

	return (ok ? 0 : -1);
}
