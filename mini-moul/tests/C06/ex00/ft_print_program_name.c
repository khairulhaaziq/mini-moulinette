// ALLOWED_FUNCTIONS: write
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include "../../../utils/constants.h"

typedef struct s_test
{
  char *desc;
  char **argv;
  char *expected;
} t_test;

int run_test(t_test test, int test_num);
char *modify_string(const char *str);

int main(void)
{
  t_test tests[] = {
      {.desc = "ft_print_program_name with one argument",
       .argv = (char *[]){"program_name", NULL},
       .expected = "./program_name\n"},
      {.desc = "ft_print_program_name with multiple arguments",
       .argv = (char *[]){"program_name", "arg1", "arg2", NULL},
       .expected = "./program_name\n"},
      {.desc = "ft_print_program_name with no arguments",
       .argv = (char *[]){"NULL"},
       .expected = "./program_name\n"},
      {.desc = "ft_print_program_name with empty string",
       .argv = (char *[]){""},
       .expected = "./program_name\n"},
      {.desc = "ft_print_program_name with long argument",
       .argv = (char *[]){"program_name", "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz", NULL},
       .expected = "./program_name\n"},
  };

  int num_tests = sizeof(tests) / sizeof(t_test);

  int overall_result = 0;

  for (int i = 0; i < num_tests; i++)
  {
    int result = run_test(tests[i], i + 1);

    if (result != 0)
    {
      overall_result = -1;
    }
  }

  return overall_result;
}

int run_test(t_test test, int test_num)
{
  fflush(stdout);
  char buf[1024];
  memset(buf, 0, sizeof(buf));
  char *program_name = "./program_name"; // Change this to your program name
  char *copy_program = "cp ../ex00/ft_print_program_name.c program_name.c";
  char *compile_command = "cc -Wall -Werror -Wextra program_name.c -o program_name"; // Change this to the compile command for your program
  FILE *fp;
  int result;

  // Compile the program
  system(copy_program);
  system(compile_command);

  // Construct the command to run
  char run_command[1024] = {0};
  strcat(run_command, program_name);
  for (int i = 1; test.argv[i]; i++)
  {
    strcat(run_command, " ");
    strcat(run_command, test.argv[i]);
  }

  // Run the program and capture its output
  fp = popen(run_command, "r");
  if (fp == NULL)
  {
    fprintf(stderr, "Failed to run command '%s': %s\n", run_command, strerror(errno));
    exit(EXIT_FAILURE);
  }

  while (fgets(buf, sizeof(buf), fp) != NULL)
  {
    if (strcmp(buf, test.expected) != 0)
    {
      printf("    " RED "[%d] %s Expected \"%s\", got \"%s\"\n" DEFAULT, test_num, test.desc, test.expected, modify_string(buf));
      result = -1;
    }
    else
    {
      printf("  " GREEN CHECKMARK GREY " [%d] %s output \"%s\" as expected\n" DEFAULT, test_num,run_command, modify_string(buf));
      result = 0;
    }
  }

  if (pclose(fp) == -1)
  {
    fprintf(stderr, "Failed to close command stream: %s\n", strerror(errno));
    exit(EXIT_FAILURE); // Remove the program executable
    if (remove(program_name) != 0)
    {
      fprintf(stderr, "Failed to remove program '%s': %s\n", program_name, strerror(errno));
      exit(EXIT_FAILURE);
    }

    if (remove("program_name.c") != 0)
    {
      fprintf(stderr, "Failed to remove program '%s': %s\n", "program_name.c", strerror(errno));
      exit(EXIT_FAILURE);
    }

    return (result);
  }

  // Remove the program executable
  if (remove(program_name) != 0)
  {
    fprintf(stderr, "Failed to remove program '%s': %s\n", program_name, strerror(errno));
    exit(EXIT_FAILURE);
  }

  if (remove("program_name.c") != 0)
  {
    fprintf(stderr, "Failed to remove program '%s': %s\n", "program_name.c", strerror(errno));
    exit(EXIT_FAILURE);
  }

  return (result);
}

char *modify_string(const char *str)
{
  int len = strlen(str);
  if (len > 0 && str[len - 1] == '\n')
  {
    char *new_str = (char *)malloc(len);
    strncpy(new_str, str, len - 1);
    new_str[len - 1] = '$';
    return new_str;
  }
  else
  {
    return strdup(str);
  }
}