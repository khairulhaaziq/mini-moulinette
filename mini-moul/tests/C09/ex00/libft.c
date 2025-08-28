#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include "../../../utils/constants.h"

char ex00_path[256] = "";

int file_exists(const char *path)
{
    return access(path, F_OK) == 0;
}

int run_command(const char *cmd)
{
    int result = system(cmd);
    return WEXITSTATUS(result);
}

void find_ex00_path(void)
{
    if (file_exists("../../../../ex00/libft_creator.sh"))
        strcpy(ex00_path, "../../../../ex00");
    else if (file_exists("../../../ex00/libft_creator.sh"))
        strcpy(ex00_path, "../../../ex00");
    else if (file_exists("../../ex00/libft_creator.sh"))
        strcpy(ex00_path, "../../ex00");
    else if (file_exists("../ex00/libft_creator.sh"))
        strcpy(ex00_path, "../ex00");
    else if (file_exists("ex00/libft_creator.sh"))
        strcpy(ex00_path, "ex00");
    else
        strcpy(ex00_path, "");
}

void cleanup_environment(void)
{
    char cmd[512];
    snprintf(cmd, sizeof(cmd), "rm -f %s/libft.a", ex00_path);
    system(cmd);
    snprintf(cmd, sizeof(cmd), "rm -f %s/test_main.c", ex00_path);
    system(cmd);
    snprintf(cmd, sizeof(cmd), "rm -f %s/test_prog", ex00_path);
    system(cmd);
}

int test_required_files(void)
{
    char path[512];
    char *required_files[] = {
        "libft_creator.sh",
        "ft_putchar.c",
        "ft_swap.c",
        "ft_putstr.c",
        "ft_strlen.c",
        "ft_strcmp.c"
    };
    int i;


    for (i = 0; i < 6; i++)
    {
        snprintf(path, sizeof(path), "%s/%s", ex00_path, required_files[i]);
        if (!file_exists(path))
        {
            printf(RED "X - %s not found\n" DEFAULT, required_files[i]);
            return 1;
        }
    }

    printf(GREEN CHECKMARK GREY " [1] Required files exist\n" DEFAULT);
    return 0;
}

int test_script_execution(void)
{
    char cmd[512];
    char path[512];


    snprintf(cmd, sizeof(cmd), "cd %s && sh libft_creator.sh >/dev/null 2>&1", ex00_path);
    if (run_command(cmd) != 0)
    {
        printf(RED "FAIL - libft_creator.sh execution failed\n" DEFAULT);
        return 1;
    }

    // Check if libft.a was created
    snprintf(path, sizeof(path), "%s/libft.a", ex00_path);
    if (!file_exists(path))
    {
        printf(RED "FAIL - libft.a not created\n" DEFAULT);
        return 1;
    }

    printf(GREEN CHECKMARK GREY " [2] libft_creator.sh can run\n" DEFAULT);
    return 0;
}

int test_library_functionality(void)
{
    char cmd[512];
    char path[512];
    FILE *test_file;


    // Ensure library exists
    snprintf(cmd, sizeof(cmd), "cd %s && sh libft_creator.sh >/dev/null 2>&1", ex00_path);
    run_command(cmd);

    snprintf(path, sizeof(path), "%s/libft.a", ex00_path);
    if (!file_exists(path))
    {
        printf(RED "FAIL - cannot build library\n" DEFAULT);
        return 1;
    }

    // Create test file
    snprintf(path, sizeof(path), "%s/test_main.c", ex00_path);
    test_file = fopen(path, "w");
    if (!test_file)
    {
        printf(RED "FAIL - cannot create test file\n" DEFAULT);
        return 1;
    }

    fprintf(test_file,
        "void ft_putchar(char c);\n"
        "void ft_swap(int *a, int *b);\n"
        "void ft_putstr(char *str);\n"
        "int ft_strlen(char *str);\n"
        "int ft_strcmp(char *s1, char *s2);\n"
        "\n"
        "int main(void) {\n"
        "    if (ft_strlen(\"hello\") != 5) return 1;\n"
        "    if (ft_strcmp(\"abc\", \"abc\") != 0) return 1;\n"
        "    int a = 5, b = 10;\n"
        "    ft_swap(&a, &b);\n"
        "    if (a != 10 || b != 5) return 1;\n"
        "    return 0;\n"
        "}\n");
    fclose(test_file);

    // Compile and link
    snprintf(cmd, sizeof(cmd), "cd %s && cc test_main.c -L. -lft -o test_prog >/dev/null 2>&1", ex00_path);
    if (run_command(cmd) != 0)
    {
        printf(RED "FAIL - cannot link with library\n" DEFAULT);
        return 1;
    }

    // Run test
    snprintf(cmd, sizeof(cmd), "cd %s && ./test_prog", ex00_path);
    if (run_command(cmd) != 0)
    {
        printf(RED "FAIL - library functions don't work correctly\n" DEFAULT);
        return 1;
    }

    printf(GREEN CHECKMARK GREY " [3] Library works\n" DEFAULT);
    return 0;
}

int main(void)
{
    int errors = 0;

    // Find ex00 directory
    find_ex00_path();

    if (strlen(ex00_path) == 0)
    {
        printf(RED "ERROR: ex00/libft_creator.sh not found\n" DEFAULT);
        return 1;
    }

    // Run tests
    errors += test_required_files();
    errors += test_script_execution();
    errors += test_library_functionality();

    // Cleanup
    cleanup_environment();

    if (errors != 0)
        printf(RED "%d test(s) failed.\n" DEFAULT, errors);

    return errors;
}
