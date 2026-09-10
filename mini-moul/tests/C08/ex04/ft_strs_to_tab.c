// ALLOWED_FUNCTIONS: malloc, free
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../utils/ft_stock_str.h"
#include "../../../../ex04/ft_strs_to_tab.c"
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
	char *strs[] = {"Hello", "mini-moulinette", ""};
	int size = 3;
	struct s_stock_str *result;
	int ok;
	int i;

	result = ft_strs_to_tab(size, strs);
	ok = (result != NULL);
	for (i = 0; ok && i < size; i++)
	{
		if (result[i].str != strs[i])
			ok = 0;
		if (result[i].size != (int)strlen(strs[i]))
			ok = 0;
		if (!result[i].copy || strcmp(result[i].copy, strs[i]) != 0)
			ok = 0;
		if (result[i].copy == result[i].str)
			ok = 0;
	}
	if (ok && result[size].str != 0)
		ok = 0;

	if (!ok)
		printf("    " RED "[1] ft_strs_to_tab() did not build the expected array (str/size/copy per element, str=0 as terminator)\n" DEFAULT);
	else
		printf("  " GREEN CHECKMARK GREY " [1] ft_strs_to_tab() built the expected array (str, size and a distinct copy per element, str=0 as terminator)\n" DEFAULT);

	if (result)
	{
		for (i = 0; i < size; i++)
		{
			if (result[i].copy && result[i].copy != result[i].str)
				free(result[i].copy);
		}
		free(result);
	}
	return (ok ? 0 : -1);
}
