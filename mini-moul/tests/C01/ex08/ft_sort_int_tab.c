// ALLOWED_FUNCTIONS: 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "../../../../ex08/ft_sort_int_tab.c"
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
	int tab[6] = {7, 6, 3, 4, 2, 5};
	int size = 6;

	ft_sort_int_tab(tab, size);

	if (tab[0] != 2 || tab[1] != 3 || tab[2] != 4 || tab[3] != 5 || tab[4] != 6 || tab[5] != 7)
	{
		printf("    " RED "[1] Failed to reverse tab.\n" DEFAULT);
		return (-1);
	}
	else
		printf("  " GREEN CHECKMARK GREY " [1] Successfully sorted tab.\n" DEFAULT);
	return (0);
}