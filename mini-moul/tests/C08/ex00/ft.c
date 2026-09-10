// ALLOWED_FUNCTIONS: 
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "../../../../ex00/ft.h"
#include "../../../utils/constants.h"

/* ex00 only asks for prototypes: define the 5 functions here with the
 * subject's exact signatures, so a wrong prototype in ft.h just won't compile. */

void ft_putchar(char c)
{
	write(1, &c, 1);
}

void ft_swap(int *a, int *b)
{
	int t;

	t = *a;
	*a = *b;
	*b = t;
}

void ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

int ft_strlen(char *str)
{
	int n;

	n = 0;
	while (str[n])
		n++;
	return (n);
}

int ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int test1(void);

int main(void)
{
	if (test1() != 0)
		return (-1);
	return (0);
}

static int read_from(int fd, char *out, int max)
{
	int n;

	n = read(fd, out, max - 1);
	if (n < 0)
		n = 0;
	out[n] = '\0';
	return (n);
}

int test1(void)
{
	int pipefd[2];
	int saved_stdout;
	int a;
	int b;
	char buffer[64];
	int ok;

	saved_stdout = dup(STDOUT_FILENO);
	pipe(pipefd);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);

	a = 1;
	b = 2;
	ft_putchar('A');
	ft_putstr("BC");
	ft_swap(&a, &b);

	fflush(stdout);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
	read_from(pipefd[0], buffer, sizeof(buffer));
	close(pipefd[0]);

	ok = (strcmp(buffer, "ABC") == 0
		&& ft_strlen("hello") == 5
		&& ft_strcmp("abc", "abc") == 0
		&& ft_strcmp("abc", "abd") < 0
		&& a == 2 && b == 1);
	if (!ok)
		printf("    " RED "[1] ft.h prototypes did not behave as expected (got putchar/putstr output \"%s\", swap gave %d,%d)\n" DEFAULT, buffer, a, b);
	else
		printf("  " GREEN CHECKMARK GREY " [1] ft.h declares the 5 functions with the expected signatures and behavior\n" DEFAULT);
	return (ok ? 0 : -1);
}
