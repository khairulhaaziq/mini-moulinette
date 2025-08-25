#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include "../../../utils/constants.h"

char ex01_path[256] = "";

int file_exists(const char *path)
{
    return access(path, F_OK) == 0;
}

int dir_exists(const char *path)
{
    struct stat st;
    return stat(path, &st) == 0 && S_ISDIR(st.st_mode);
}

int run_command(const char *cmd)
{
    int result = system(cmd);
    return WEXITSTATUS(result);
}

void find_ex01_path(void)
{
    if (file_exists("../../../../ex01/Makefile"))
        strcpy(ex01_path, "../../../../ex01");
    else if (file_exists("../../../ex01/Makefile"))
        strcpy(ex01_path, "../../../ex01");
    else if (file_exists("../../ex01/Makefile"))
        strcpy(ex01_path, "../../ex01");
    else if (file_exists("../ex01/Makefile"))
        strcpy(ex01_path, "../ex01");
    else if (file_exists("ex01/Makefile"))
        strcpy(ex01_path, "ex01");
    else
        strcpy(ex01_path, "");
}

void setup_environment(void)
{
    char cmd[1024];

    // Create directories
    snprintf(cmd, sizeof(cmd), "mkdir -p %s/srcs", ex01_path);
    system(cmd);
    snprintf(cmd, sizeof(cmd), "mkdir -p %s/includes", ex01_path);
    system(cmd);

    // Copy source files
    snprintf(cmd, sizeof(cmd), "cp tests/C09/ex01/my_srcs/* %s/srcs/ 2>/dev/null", ex01_path);
    if (system(cmd) != 0) {
        snprintf(cmd, sizeof(cmd), "cp */tests/C09/ex01/my_srcs/* %s/srcs/ 2>/dev/null", ex01_path);
        if (system(cmd) != 0) {
            snprintf(cmd, sizeof(cmd), "cp mini-moul/tests/C09/ex01/my_srcs/* %s/srcs/ 2>/dev/null", ex01_path);
            system(cmd);
        }
    }

    // Copy header files
    snprintf(cmd, sizeof(cmd), "cp tests/C09/ex01/my_includes/* %s/includes/ 2>/dev/null", ex01_path);
    if (system(cmd) != 0) {
        snprintf(cmd, sizeof(cmd), "cp */tests/C09/ex01/my_includes/* %s/includes/ 2>/dev/null", ex01_path);
        if (system(cmd) != 0) {
            snprintf(cmd, sizeof(cmd), "cp mini-moul/tests/C09/ex01/my_includes/* %s/includes/ 2>/dev/null", ex01_path);
            system(cmd);
        }
    }
}

void cleanup_environment(void)
{
    char cmd[512];
    snprintf(cmd, sizeof(cmd), "cd %s && make fclean >/dev/null 2>&1", ex01_path);
    system(cmd);
    snprintf(cmd, sizeof(cmd), "rm -rf %s/srcs", ex01_path);
    system(cmd);
    snprintf(cmd, sizeof(cmd), "rm -rf %s/includes", ex01_path);
    system(cmd);
    snprintf(cmd, sizeof(cmd), "rm -f %s/test_main.c", ex01_path);
    system(cmd);
    snprintf(cmd, sizeof(cmd), "rm -f %s/test_prog", ex01_path);
    system(cmd);
}

int test_make_all(void)
{
    char cmd[512];
    char path[512];


    snprintf(cmd, sizeof(cmd), "cd %s && make all >/dev/null 2>&1", ex01_path);
    if (run_command(cmd) != 0)
    {
        printf(RED "FAIL - make all failed\n" DEFAULT);
        return 1;
    }

    snprintf(path, sizeof(path), "%s/libft.a", ex01_path);
    if (!file_exists(path))
    {
        printf(RED "FAIL - libft.a not created\n" DEFAULT);
        return 1;
    }

    // Check object files
    snprintf(path, sizeof(path), "%s/srcs/ft_putchar.o", ex01_path);
    if (!file_exists(path))
    {
        printf(RED "FAIL - object files not in srcs directory\n" DEFAULT);
        return 1;
    }

    printf(GREEN CHECKMARK GREY " [1] make all works\n" DEFAULT);
    return 0;
}

int test_make_clean(void)
{
    char cmd[512];
    char path[512];


    snprintf(cmd, sizeof(cmd), "cd %s && make clean >/dev/null 2>&1", ex01_path);
    if (run_command(cmd) != 0)
    {
        printf(RED "FAIL - make clean failed\n" DEFAULT);
        return 1;
    }

    // Object files should be gone
    snprintf(path, sizeof(path), "%s/srcs/ft_putchar.o", ex01_path);
    if (file_exists(path))
    {
        printf(RED "FAIL - object files still exist after clean\n" DEFAULT);
        return 1;
    }

    // Library should still exist
    snprintf(path, sizeof(path), "%s/libft.a", ex01_path);
    if (!file_exists(path))
    {
        printf(RED "FAIL - libft.a removed by clean\n" DEFAULT);
        return 1;
    }

    printf(GREEN CHECKMARK GREY " [2] make clean works\n" DEFAULT);
    return 0;
}

int test_make_fclean(void)
{
    char cmd[512];
    char path[512];


    // Rebuild first
    snprintf(cmd, sizeof(cmd), "cd %s && make all >/dev/null 2>&1", ex01_path);
    run_command(cmd);

    snprintf(cmd, sizeof(cmd), "cd %s && make fclean >/dev/null 2>&1", ex01_path);
    if (run_command(cmd) != 0)
    {
        printf(RED "FAIL - make fclean failed\n" DEFAULT);
        return 1;
    }

    // Everything should be gone
    snprintf(path, sizeof(path), "%s/libft.a", ex01_path);
    if (file_exists(path))
    {
        printf(RED "FAIL - libft.a still exists after fclean\n" DEFAULT);
        return 1;
    }

    snprintf(path, sizeof(path), "%s/srcs/ft_putchar.o", ex01_path);
    if (file_exists(path))
    {
        printf(RED "FAIL - object files still exist after fclean\n" DEFAULT);
        return 1;
    }

    printf(GREEN CHECKMARK GREY " [3] make fclean works\n" DEFAULT);
    return 0;
}

int test_make_re(void)
{
    char cmd[512];
    char path[512];
    struct stat st_lib;
    time_t old_lib_time = 0;


    // Build first
    snprintf(cmd, sizeof(cmd), "cd %s && make all >/dev/null 2>&1", ex01_path);
    run_command(cmd);

    snprintf(path, sizeof(path), "%s/libft.a", ex01_path);
    if (stat(path, &st_lib) == 0)
        old_lib_time = st_lib.st_mtime;

    sleep(1);

    snprintf(cmd, sizeof(cmd), "cd %s && make re >/dev/null 2>&1", ex01_path);
    if (run_command(cmd) != 0)
    {
        printf(RED "FAIL - make re failed\n" DEFAULT);
        return 1;
    }

    if (!file_exists(path))
    {
        printf(RED "FAIL - libft.a not created by re\n" DEFAULT);
        return 1;
    }

    time_t new_lib_time = 0;
    if (stat(path, &st_lib) == 0)
        new_lib_time = st_lib.st_mtime;

    if (new_lib_time <= old_lib_time)
    {
        printf(RED "FAIL - library not rebuilt by re\n" DEFAULT);
        return 1;
    }

    printf(GREEN CHECKMARK GREY " [4] make re works\n" DEFAULT);
    return 0;
}

int test_library_functionality(void)
{
    char cmd[512];
    char path[512];
    FILE *test_file;


    // Ensure library exists
    snprintf(cmd, sizeof(cmd), "cd %s && make all >/dev/null 2>&1", ex01_path);
    run_command(cmd);

    snprintf(path, sizeof(path), "%s/libft.a", ex01_path);
    if (!file_exists(path))
    {
        printf(RED "FAIL - cannot build library\n" DEFAULT);
        return 1;
    }

    // Create test file
    snprintf(path, sizeof(path), "%s/test_main.c", ex01_path);
    test_file = fopen(path, "w");
    if (!test_file)
    {
        printf(RED "FAIL - cannot create test file\n" DEFAULT);
        return 1;
    }

    fprintf(test_file,
        "#include \"includes/ft.h\"\n"
        "int main(void) {\n"
        "    if (ft_strlen(\"hello\") != 5) return 1;\n"
        "    if (ft_strcmp(\"abc\", \"abc\") != 0) return 1;\n"
        "    return 0;\n"
        "}\n");
    fclose(test_file);

    // Compile and link
    snprintf(cmd, sizeof(cmd), "cd %s && cc test_main.c -L. -lft -o test_prog >/dev/null 2>&1", ex01_path);
    if (run_command(cmd) != 0)
    {
        printf(RED "FAIL - cannot link with library\n" DEFAULT);
        return 1;
    }

    // Run test
    snprintf(cmd, sizeof(cmd), "cd %s && ./test_prog", ex01_path);
    if (run_command(cmd) != 0)
    {
        printf(RED "FAIL - library functions don't work correctly\n" DEFAULT);
        return 1;
    }

    printf(GREEN CHECKMARK GREY " [5] Library functions correctly\n" DEFAULT);
    return 0;
}

int main(void)
{
    int errors = 0;
    char path[512];

    // Find ex01 directory
    find_ex01_path();

    if (strlen(ex01_path) == 0)
    {
        printf(RED "ERROR: ex01/Makefile not found\n" DEFAULT);
        return 1;
    }

    // Setup environment
    setup_environment();

    // Check if files were copied
    snprintf(path, sizeof(path), "%s/srcs/ft_putchar.c", ex01_path);
    if (!file_exists(path))
    {
        printf(RED "ERROR: Could not copy test files\n" DEFAULT);
        cleanup_environment();
        return 1;
    }

    // Run tests
    errors += test_make_all();
    errors += test_make_clean();
    errors += test_make_fclean();
    errors += test_make_re();
    errors += test_library_functionality();

    // Cleanup
    cleanup_environment();

    if (errors != 0)
        printf(RED "%d test(s) failed.\n" DEFAULT, errors);

    return errors;
}
