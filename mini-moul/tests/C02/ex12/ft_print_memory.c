// ALLOWED_FUNCTIONS: write
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "../../../../ex12/ft_print_memory.c"
#include "../../../utils/constants.h"

int test1(void);
int test2(void);

int main(void)
{
	int error = 0;

	if (test1() != 0)
		error -= 1;
	if (test2() != 0)
		error -= 1;
	return (error);
}

static int moul_is_printable(unsigned char c)
{
	return (c >= 32 && c <= 126);
}

static int hex_digit_value(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	return (-1);
}

// Tolerates any address width/padding and hex-column spacing: only the
// "<address>:", hex bytes, then trailing ascii column are checked strictly.
static int check_line(char *line, unsigned char *buf, size_t line_index, size_t bytes_in_line)
{
	char *colon;
	char *content;
	size_t content_len;
	size_t ascii_start;
	char *ascii_part;
	unsigned long addr_value;
	unsigned long expected_addr;
	size_t i;
	size_t hex_count;
	char decoded[32];
	char *p;

	colon = strchr(line, ':');
	if (!colon)
	{
		printf("    " RED "line \"%s\" is missing ':' after the address\n" DEFAULT, line);
		return (0);
	}
	*colon = '\0';
	p = line;
	if (p[0] == '0' && (p[1] == 'x' || p[1] == 'X'))
		p += 2;
	if (*p == '\0')
	{
		printf("    " RED "line %zu has an empty address\n" DEFAULT, line_index + 1);
		return (0);
	}
	for (i = 0; p[i]; i++)
	{
		if (hex_digit_value(p[i]) == -1)
		{
			printf("    " RED "line %zu has an invalid address \"%s\"\n" DEFAULT, line_index + 1, line);
			return (0);
		}
	}
	addr_value = strtoul(p, NULL, 16);
	expected_addr = (unsigned long)(buf + line_index * 16);
	if (addr_value != expected_addr)
	{
		printf("    " RED "line %zu expected address %lx, got %s\n" DEFAULT, line_index + 1, expected_addr, line);
		return (0);
	}

	content = colon + 1;
	content_len = strlen(content);
	if (content_len < bytes_in_line)
	{
		printf("    " RED "line %zu is too short: \"%s\"\n" DEFAULT, line_index + 1, content);
		return (0);
	}
	ascii_start = content_len - bytes_in_line;
	ascii_part = content + ascii_start;
	for (i = 0; i < bytes_in_line; i++)
	{
		unsigned char byte = buf[line_index * 16 + i];
		char expected_char = moul_is_printable(byte) ? (char)byte : '.';

		if (ascii_part[i] != expected_char)
		{
			printf("    " RED "line %zu ascii column mismatch at byte %zu: expected '%c', got '%c'\n" DEFAULT, line_index + 1, i, expected_char, ascii_part[i]);
			return (0);
		}
	}

	hex_count = 0;
	for (i = 0; i < ascii_start; i++)
	{
		if (content[i] == ' ')
			continue;
		if (hex_digit_value(content[i]) == -1)
		{
			printf("    " RED "line %zu has an unexpected character '%c' in the hex column\n" DEFAULT, line_index + 1, content[i]);
			return (0);
		}
		if (hex_count >= bytes_in_line * 2)
		{
			printf("    " RED "line %zu has too many hex digits before the ascii column\n" DEFAULT, line_index + 1);
			return (0);
		}
		decoded[hex_count] = content[i];
		hex_count++;
	}
	if (hex_count != bytes_in_line * 2)
	{
		printf("    " RED "line %zu expected %zu hex digits, got %zu\n" DEFAULT, line_index + 1, bytes_in_line * 2, hex_count);
		return (0);
	}
	for (i = 0; i < bytes_in_line; i++)
	{
		unsigned char decoded_byte = (unsigned char)((hex_digit_value(decoded[i * 2]) << 4) | hex_digit_value(decoded[i * 2 + 1]));

		if (decoded_byte != buf[line_index * 16 + i])
		{
			printf("    " RED "line %zu hex byte %zu mismatch: expected %02x, got %02x\n" DEFAULT, line_index + 1, i, buf[line_index * 16 + i], decoded_byte);
			return (0);
		}
	}
	return (1);
}

static int run_case(char *desc, unsigned char *buf, size_t size)
{
	int saved_stdout;
	int output_fd;
	void *ret;
	FILE *fp;
	char *output;
	long output_len;
	char *lines[64];
	int line_count;
	size_t total_lines;
	size_t line;
	int ok;
	char *cursor;

	fflush(stdout);
	saved_stdout = dup(STDOUT_FILENO);
	output_fd = open("output_c02_ex12.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	dup2(output_fd, STDOUT_FILENO);
	close(output_fd);

	ret = ft_print_memory(buf, (unsigned int)size);

	fflush(stdout);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);

	fp = fopen("output_c02_ex12.txt", "r");
	fseek(fp, 0, SEEK_END);
	output_len = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	output = malloc((size_t)output_len + 1);
	if (output_len > 0)
		fread(output, 1, (size_t)output_len, fp);
	output[output_len] = '\0';
	fclose(fp);
	remove("output_c02_ex12.txt");

	ok = 1;
	if (ret != (void *)buf)
	{
		printf("    " RED "[%s] Expected return value %p, got %p\n" DEFAULT, desc, (void *)buf, ret);
		ok = 0;
	}

	if (size == 0)
	{
		if (output_len != 0)
		{
			printf("    " RED "[%s] Expected no output for size 0, got \"%s\"\n" DEFAULT, desc, output);
			ok = 0;
		}
	}
	else
	{
		total_lines = (size + 15) / 16;
		line_count = 0;
		cursor = output;
		while (*cursor && line_count < 64)
		{
			char *nl = strchr(cursor, '\n');

			if (!nl)
				break;
			*nl = '\0';
			lines[line_count] = cursor;
			line_count++;
			cursor = nl + 1;
		}
		if ((size_t)line_count != total_lines || *cursor != '\0')
		{
			printf("    " RED "[%s] Expected %zu lines of output, got %d (trailing: \"%s\")\n" DEFAULT, desc, total_lines, line_count, cursor);
			ok = 0;
		}
		else
		{
			for (line = 0; line < total_lines; line++)
			{
				size_t bytes_in_line = (line == total_lines - 1) ? (size - line * 16) : 16;

				if (!check_line(lines[line], buf, line, bytes_in_line))
				{
					ok = 0;
					break;
				}
			}
		}
	}

	if (ok)
		printf("  " GREEN CHECKMARK GREY " [%s] output matches the expected format\n" DEFAULT, desc);

	free(output);
	return (ok ? 0 : -1);
}

int test1(void)
{
	unsigned char buf[35];
	size_t i;

	for (i = 0; i < sizeof(buf); i++)
		buf[i] = (unsigned char)((i * 7 + 3) % 256);
	buf[5] = 'H';
	buf[6] = 'i';
	buf[10] = 0;
	return (run_case("ft_print_memory() with 35 bytes spanning 3 lines", buf, sizeof(buf)));
}

int test2(void)
{
	unsigned char buf[4] = {0, 0, 0, 0};

	return (run_case("ft_print_memory() with size 0", buf, 0));
}
