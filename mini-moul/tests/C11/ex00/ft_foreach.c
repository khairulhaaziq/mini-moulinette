// ALLOWED_FUNCTIONS: 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../../ex00/ft_foreach.c"
#include "../../../utils/constants.h"

static int g_calls[64];
static int g_call_count;

static void moul_record(int n)
{
	if (g_call_count < 64)
		g_calls[g_call_count] = n;
	g_call_count++;
}

typedef struct s_test
{
	char *desc;
	int *tab;
	int length;
} t_test;

int run_tests(t_test *tests, int count);

int main(void)
{
	int tab1[] = {1, 2, 3, 4, 5};
	int tab2[] = {42};
	int tab3[] = {-3, 0, 7, -8, 15, 100};
	t_test tests[] = {
		{.desc = "ft_foreach on {1, 2, 3, 4, 5}", .tab = tab1, .length = 5},
		{.desc = "ft_foreach on {42}", .tab = tab2, .length = 1},
		{.desc = "ft_foreach on {-3, 0, 7, -8, 15, 100}", .tab = tab3, .length = 6},
	};
	int count = sizeof(tests) / sizeof(tests[0]);

	return (run_tests(tests, count));
}

int run_tests(t_test *tests, int count)
{
	int i;
	int j;
	int error = 0;

	for (i = 0; i < count; i++)
	{
		int ok = 1;

		g_call_count = 0;
		ft_foreach(tests[i].tab, tests[i].length, &moul_record);
		if (g_call_count != tests[i].length)
			ok = 0;
		else
		{
			for (j = 0; j < tests[i].length; j++)
			{
				if (g_calls[j] != tests[i].tab[j])
				{
					ok = 0;
					break;
				}
			}
		}
		if (!ok)
		{
			printf("    " RED "[%d] %s did not call f on every element, in order\n" DEFAULT, i + 1, tests[i].desc);
			error -= 1;
		}
		else
			printf("  " GREEN CHECKMARK GREY " [%d] %s called f on every element, in order\n" DEFAULT, i + 1, tests[i].desc);
	}
	return (error);
}
