// ALLOWED_FUNCTIONS: 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "../../../../ex03/ft_div_mod.c"
#include "../../../utils/constants.h"

int test1(void);
int test2(void);
int test3(void);

int main(void)
{
	if (test1()+test2()+test3() != 0)
		return (-1);
	return (0);
}

int test1(void)
{
	int a;
	int b;
	int x;
	int y;

	a = 10;
	b = 5;
	ft_div_mod(a, b, &x, &y);


	if (x != 2 || y != 0)
	{
		printf("    " RED "[1] ft_div_mod(10, 5, &x, &y) Expected x = 2, got %d. Expected y = 0, got %d\n" DEFAULT, x, y);
		return (-1);
	}
	else
		printf("  " GREEN CHECKMARK GREY " [1] ft_div_mod(10, 5, &x, &y) Expected x = 2, got %d. Expected y = 0, got %d\n" DEFAULT, x, y);
	return (0);
}

int test2(void)
{
	int a;
	int b;
	int x;
	int y;

	a = 25;
	b = 6;
	ft_div_mod(a, b, &x, &y);


	if (x != 4 || y != 1)
	{
		printf("    " RED "[2] ft_div_mod(25, 6, &x, &y) Expected x = 4, got %d. Expected y = 1, got %d\n" DEFAULT, x, y);
		return (-1);
	}
	else
		printf("  " GREEN CHECKMARK GREY " [2] ft_div_mod(25, 6, &x, &y) Expected x = 4, got %d. Expected y = 1, got %d\n" DEFAULT, x, y);
	return (0);
}

int test3(void)
{
	int a;
	int b;
	int x;
	int y;

	a = 47;
	b = 8;
	ft_div_mod(a, b, &x, &y);


	if (x != 5 || y != 7)
	{
		printf("    " RED "[3] ft_div_mod(47, 8, &x, &y) Expected x = 5, got %d. Expected y = 7, got %d\n" DEFAULT, x, y);
		return (-1);
	}
	else
		printf("  " GREEN CHECKMARK GREY " [3] ft_div_mod(47, 8, &x, &y) Expected x = 5, got %d. Expected y = 7, got %d\n" DEFAULT, x, y);
	return (0);
}