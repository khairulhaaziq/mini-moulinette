// ALLOWED_FUNCTIONS: 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "../../../../ex00/ft_ft.c"
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
	int	*nbr;
	int	number = 33;
	int	expected_output;

	nbr = &number;
	ft_ft(nbr);
	expected_output = 42;
	if (number != expected_output)
	{
		printf("    " RED "[1] ft_ft() Expected %d, got %d\n"DEFAULT, expected_output, number);
		return (-1);
	}
	else
		printf("  " GREEN CHECKMARK GREY " [1] ft_ft() Expected %d, got %d\n"DEFAULT, expected_output, number);
	return (0);
}