// ALLOWED_FUNCTIONS: 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../../ex09/ft_strcapitalize.c"
#include "../../../utils/constants.h"

typedef struct s_test
{
	char *desc;
	char *src;
	char *expected;
} t_test;

int run_tests(t_test *tests, int count);

int main(void)
{
	t_test tests[] = {
	    {.desc = "ft_strcapitalize(\"salut, comment tu vas ? 42mots quarante-deux; cinquante+et+un\")",
	     .src = "salut, comment tu vas ? 42mots quarante-deux; cinquante+et+un",
	     .expected = "Salut, Comment Tu Vas ? 42mots Quarante-Deux; Cinquante+Et+Un"},
	    {.desc = "ft_strcapitalize(\"\")",
	     .src = "",
	     .expected = ""},
	    {.desc = "ft_strcapitalize(\"a\")",
	     .src = "a",
	     .expected = "A"},
	    {.desc = "ft_strcapitalize(\"HELLO\")",
	     .src = "HELLO",
	     .expected = "Hello"},
	    {.desc = "ft_strcapitalize(\"hello\")",
	     .src = "hello",
	     .expected = "Hello"},
	    {.desc = "ft_strcapitalize(\"   hello\")",
	     .src = "   hello",
	     .expected = "   Hello"},
	    {.desc = "ft_strcapitalize(\"hello   \")",
	     .src = "hello   ",
	     .expected = "Hello   "},
	    {.desc = "ft_strcapitalize(\"hello   world\")",
	     .src = "hello   world",
	     .expected = "Hello   World"},
	    {.desc = "ft_strcapitalize(\"a1b2c3d4e5f6g7h8i9j0\")",
	     .src = "a1b2c3d4e5f6g7h8i9j0",
	     .expected = "A1b2c3d4e5f6g7h8i9j0"},
	    {.desc = "ft_strcapitalize(\"123AA\") lowercases letters after a digit, mid-word",
	     .src = "123AA",
	     .expected = "123aa"},
	    {.desc = "ft_strcapitalize(\"9Test\") a digit at the start of a word blocks capitalization",
	     .src = "9Test",
	     .expected = "9test"},
	    {.desc = "ft_strcapitalize(\"!@#$%^&*()_+-=[]{}\\|;':\",./<>?\")",
	     .src = "!@#$%^&*()_+-=[]{}\\|;':\",./<>?",
	     .expected = "!@#$%^&*()_+-=[]{}\\|;':\",./<>?"},
	};
	int count = sizeof(tests) / sizeof(tests[0]);

	return (run_tests(tests, count));
}

int run_tests(t_test *tests, int count)
{
	int i;
	int error = 0;

	for (i = 0; i < count; i++)
	{
		char *result = malloc(sizeof(char) * (strlen(tests[i].src) + 1));
		if (result == NULL)
		{
			perror("Error: malloc failed");
			exit(EXIT_FAILURE);
		}

		strcpy(result, tests[i].src);
		ft_strcapitalize(result);

		if (strcmp(result, tests[i].expected) != 0)
		{
			printf("    " RED "[%d] %s Expected \"%s\", got \"%s\"\n", i + 1, tests[i].desc, tests[i].expected, result);
			error -= 1;
		}
		else
			printf("  " GREEN CHECKMARK GREY " [%d] %s Expected \"%s\", got \"%s\"\n" DEFAULT, i + 1, tests[i].desc, tests[i].expected, result);

		free(result);
	}

	return (error);
}
