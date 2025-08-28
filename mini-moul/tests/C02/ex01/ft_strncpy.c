#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../../ex01/ft_strncpy.c"
#include "../../../utils/constants.h"

int	test1(void)
{
	char src[] = "Hello";
	char dest[] = "World1";
	char *result;

	result = ft_strncpy(dest, src, 3);

	if (strcmp(result, "Helld1") != 0)
	{
		printf("    " RED "[1] ft_strncpy(\"World1\", \"Hello\", 3) Expected \"Helld1\", got \"%s\"\n", result);
		return (-1);
	}
	else
		printf("  " GREEN CHECKMARK GREY " [1] ft_strncpy(\"World1\", \"Hello\", 3) Expected \"Helld1\", got \"%s\"\n" DEFAULT, result);
	return (0);
}

int	test2(void)
{
	char src[] = "Hello";
	char dest[] = "World1";
	char *result;

	result = ft_strncpy(dest, src, 5);

	if (strcmp(result, "Hello1") != 0)
	{
		printf("    " RED "[2] ft_strncpy(\"World1\", \"Hello\", 5) Expected \"Hello1\", got \"%s\"\n", result);
		return (-1);
	}
	else
		printf("  " GREEN CHECKMARK GREY " [2] ft_strncpy(\"World1\", \"Hello\", 5) Expected \"Hello1\", got \"%s\"\n" DEFAULT, result);
	return (0);
}

int	test3(void)
{
	char src[] = "Hello";
	char dest[] = "World1";
	char *result;

	result = ft_strncpy(dest, src, 7);

	if (strcmp(result, "Hello") != 0)
	{
		printf("    " RED "[3] ft_strncpy(\"World1\", \"Hello\", 7) Expected \"Hello\", got \"%s\"\n", result);
		return (-1);
	}
	else
		printf("  " GREEN CHECKMARK GREY " [3] ft_strncpy(\"World1\", \"Hello\", 7) Expected \"Hello\", got \"%s\"\n" DEFAULT, result);
	return (0);
}

int	test4(void)
{
	char src[] = "Hello";
	char dest[15];
	int i;

	memset(dest, 'X', sizeof(dest));
	dest[10] = 'S'; // sentinel to detect overwrite beyond n
	ft_strncpy(dest, src, 10);
	for (i = 0; i < 5; i++)
	{
		if (dest[i] != src[i])
		{
			printf("    " RED "[4] ft_strncpy(\"World1\", \"Hello\", 10) Expected '%c', got '%c'\n", src[i], dest[i]);
			return (-1);
		}
	}
	for (; i < 10; i++)
	{
		if (dest[i] != '\0')
		{
			printf("    " RED "[4] ft_strncpy(\"World1\", \"Hello\", 10) Expected '\\0' padding, got '%d'\n", dest[i]);
			return (-1);
		}
	}
	// sentinel check: ensure padding stops at n and sentinel is preserved
	if (dest[10] != 'S')
	{
		printf("    " RED "[4] ft_strncpy overwritten sentinel at index 10, got '%c'\n", dest[10]);
		return (-1);
	}
	// verify that tail beyond n remains unchanged
	for (i = 11; i < (int)sizeof(dest); i++)
	{
		if (dest[i] != 'X')
		{
			printf("    " RED "[4] ft_strncpy tail beyond 10 corrupted at index %d, got '%c'\n", i, dest[i]);
			return (-1);
		}
	}
	printf("  " GREEN CHECKMARK GREY " [4] ft_strncpy properly padded with '\\0' and left tail unchanged\n" DEFAULT);
	return (0);
}

int	main(void)
{
	if (test1()+test2()+test3()+test4()!=0)
		return (-1);
	return (0);
}
