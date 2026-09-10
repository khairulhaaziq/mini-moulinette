// ALLOWED_FUNCTIONS: 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "../../../../ex04/ft_ultimate_div_mod.c"
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
	int x;
	int	y;

	x = 15;
	y = 3;
	ft_ultimate_div_mod(&x, &y);

	if (x != 5 || y != 0)
	{
		printf("    " RED "[1] ft_ultimate_div_mod(x = 15, y = 3) Expected x = 5, got %d. Expected y = 0, got %d\n" DEFAULT, x, y);
		return (-1);
	}
	else
		printf("  " GREEN CHECKMARK GREY " [1] ft_ultimate_div_mod(x = 15, y = 3) Expected x = 5, got %d. Expected y = 0, got %d\n" DEFAULT, x, y);
	return (0);
}

int test2(void)
{
	int x;
	int	y;

	x = 23;
	y = 5;
	ft_ultimate_div_mod(&x, &y);

	if (x != 4 || y != 3)
	{
		printf("    " RED "[2] ft_ultimate_div_mod(x = 23, y = 5) Expected x = 4, got %d. Expected y = 3, got %d\n" DEFAULT, x, y);
		return (-1);
	}
	else
		printf("  " GREEN CHECKMARK GREY " [2] ft_ultimate_div_mod(x = 23, y = 5) Expected x = 4, got %d. Expected y = 3, got %d\n" DEFAULT, x, y);
	return (0);
}

int test3(void)
{
	int x;
	int	y;

	x = 32;
	y = 5;
	ft_ultimate_div_mod(&x, &y);

	if (x != 6 || y != 2)
	{
		printf("    " RED "[3] ft_ultimate_div_mod(x = 32, y = 5) Expected x = 6, got %d. Expected y = 2, got %d\n" DEFAULT, x, y);
		return (-1);
	}
	else
		printf("  " GREEN CHECKMARK GREY " [3] ft_ultimate_div_mod(x = 32, y = 5) Expected x = 6, got %d. Expected y = 2, got %d\n" DEFAULT, x, y);
	return (0);
}