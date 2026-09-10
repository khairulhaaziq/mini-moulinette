// ALLOWED_FUNCTIONS: close, open, read, write, malloc, free, strerror, basename
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../utils/constants.h"

static int moul_is_printable(unsigned char c)
{
	return (c >= 32 && c <= 126);
}

/* matches `hexdump -C` byte for byte: 16 bytes per line, an extra gap
 * after the 8th byte, and a trailing offset-only line once size > 0. */
static void moul_expected_hexdump(unsigned char *buf, unsigned int size, char *out)
{
	unsigned int offset;
	unsigned int i;
	unsigned int chunk;
	char *p;

	p = out;
	offset = 0;
	while (offset < size)
	{
		chunk = (size - offset < 16) ? (size - offset) : 16;
		p += sprintf(p, "%08x  ", offset);
		for (i = 0; i < 16; i++)
		{
			if (i < chunk)
				p += sprintf(p, "%02x ", buf[offset + i]);
			else
				p += sprintf(p, "   ");
			if (i == 7)
				p += sprintf(p, " ");
		}
		p += sprintf(p, " |");
		for (i = 0; i < chunk; i++)
			*p++ = moul_is_printable(buf[offset + i]) ? (char)buf[offset + i] : '.';
		p += sprintf(p, "|\n");
		offset += chunk;
	}
	if (size > 0)
		p += sprintf(p, "%08x\n", size);
	*p = '\0';
}

int test1(void);
int test2(void);
int test3(void);

int main(void)
{
	int error = 0;

	if (system("make -C ../ex03 > /dev/null 2>&1") != 0)
	{
		printf("    " RED "[0] make did not build ft_hexdump\n" DEFAULT);
		return (-1);
	}
	if (test1() != 0)
		error -= 1;
	if (test2() != 0)
		error -= 1;
	if (test3() != 0)
		error -= 1;
	system("make -C ../ex03 fclean > /dev/null 2>&1");
	return (error);
}

static int run_case(char *desc, unsigned char *buf, unsigned int size)
{
	FILE *fp;
	char expected[8192];
	char actual[8192];
	size_t n;
	int ok;

	fp = fopen("moul_hexdump_input.bin", "wb");
	fwrite(buf, 1, size, fp);
	fclose(fp);

	moul_expected_hexdump(buf, size, expected);

	fp = popen("../ex03/ft_hexdump -C moul_hexdump_input.bin 2> /dev/null", "r");
	n = fread(actual, 1, sizeof(actual) - 1, fp);
	actual[n] = '\0';
	pclose(fp);

	ok = (strcmp(expected, actual) == 0);
	if (!ok)
		printf("    " RED "[%s] output did not match, expected:\n%s---\ngot:\n%s---\n" DEFAULT, desc, expected, actual);
	else
		printf("  " GREEN CHECKMARK GREY " [%s] output matched hexdump -C exactly\n" DEFAULT, desc);

	remove("moul_hexdump_input.bin");
	return (ok ? 0 : -1);
}

int test1(void)
{
	unsigned char buf[45];
	unsigned int i;

	for (i = 0; i < sizeof(buf); i++)
		buf[i] = (unsigned char)((i * 7 + 3) % 256);
	buf[5] = 'H';
	buf[6] = 'i';
	return (run_case("ft_hexdump -C on 45 mixed bytes", buf, sizeof(buf)));
}

int test2(void)
{
	unsigned char buf[16] = "0123456789abcdef";

	return (run_case("ft_hexdump -C on exactly 16 bytes", buf, sizeof(buf)));
}

int test3(void)
{
	unsigned char buf[1];

	return (run_case("ft_hexdump -C on an empty file", buf, 0));
}
