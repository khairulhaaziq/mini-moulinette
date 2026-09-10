// ALLOWED_FUNCTIONS: write
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../../../utils/ft_stock_str.h"
#include "../../../../ex05/ft_show_tab.c"
#include "../../../utils/constants.h"

int test1(void);

int main(void)
{
	if (test1() != 0)
		return (-1);
	return (0);
}

int test1(void)
{
	struct s_stock_str tab[3];
	char copy0[] = "Hello";
	char copy1[] = "modified";
	int pipefd[2];
	int saved_stdout;
	char buffer[256];
	int n;
	int ok;

	tab[0].str = "Hello";
	tab[0].size = 5;
	tab[0].copy = copy0;
	tab[1].str = "World";
	tab[1].size = 5;
	tab[1].copy = copy1;
	tab[2].str = 0;

	saved_stdout = dup(STDOUT_FILENO);
	pipe(pipefd);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);

	ft_show_tab(tab);

	fflush(stdout);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
	n = read(pipefd[0], buffer, sizeof(buffer) - 1);
	if (n < 0)
		n = 0;
	buffer[n] = '\0';
	close(pipefd[0]);

	ok = (strcmp(buffer, "Hello\n5\nHello\nWorld\n5\nmodified\n") == 0);
	if (!ok)
		printf("    " RED "[1] ft_show_tab() Expected \"Hello\\n5\\nHello\\nWorld\\n5\\nmodified\\n\", got \"%s\"\n" DEFAULT, buffer);
	else
		printf("  " GREEN CHECKMARK GREY " [1] ft_show_tab() printed str, size and copy for each element as expected\n" DEFAULT);
	return (ok ? 0 : -1);
}
