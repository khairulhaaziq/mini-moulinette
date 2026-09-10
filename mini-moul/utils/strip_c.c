#include <stdio.h>

/* Blanks out comments and string/char literal contents from a C file on
 * stdin (keeps newlines), so check_forbidden.sh doesn't mistake a name
 * in a comment or a string for an actual call. */

int main(void)
{
	int c;
	int c2;
	int last;

	while ((c = getchar()) != EOF)
	{
		if (c == '/')
		{
			c2 = getchar();
			if (c2 == '/')
			{
				while ((c = getchar()) != EOF && c != '\n')
					;
				if (c == '\n')
					putchar('\n');
			}
			else if (c2 == '*')
			{
				last = 0;
				while ((c = getchar()) != EOF)
				{
					if (last == '*' && c == '/')
						break;
					if (c == '\n')
						putchar('\n');
					last = c;
				}
			}
			else
			{
				putchar('/');
				if (c2 != EOF)
					ungetc(c2, stdin);
			}
		}
		else if (c == '"')
		{
			while ((c = getchar()) != EOF && c != '"')
			{
				if (c == '\\')
					getchar();
			}
		}
		else if (c == '\'')
		{
			while ((c = getchar()) != EOF && c != '\'')
			{
				if (c == '\\')
					getchar();
			}
		}
		else
			putchar(c);
	}
	return (0);
}
