// ALLOWED_FUNCTIONS: 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "../../../../ex01/ft_ultimate_ft.c"
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
	int n;
	int *nbr8;
	int **nbr7;
	int ***nbr6;
	int ****nbr5;
	int *****nbr4;
	int ******nbr3;
	int *******nbr2;
	int ********nbr1;
	int *********nbr;
	int expected_output;

	n = 21;

	nbr8 = &n;
	nbr7 = &nbr8;
	nbr6 = &nbr7;
	nbr5 = &nbr6;
	nbr4 = &nbr5;
	nbr3 = &nbr4;
	nbr2 = &nbr3;
	nbr1 = &nbr2;
	nbr = &nbr1;

	ft_ultimate_ft(nbr);
	expected_output = 42;
	if (n != expected_output)
	{
		printf("    " RED "[1] ft_ultimate_ft() Expected %d, got %d\n"DEFAULT, expected_output, n);
		return (-1);
	}
	else
		printf("  " GREEN CHECKMARK GREY " [1] ft_ultimate_ft() Expected %d, got %d\n"DEFAULT, expected_output, n);
	return (0);
}