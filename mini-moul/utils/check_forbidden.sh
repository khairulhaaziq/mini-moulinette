# Detects calls to common libc/POSIX functions not in the exercise's
# "Allowed functions" list. Sourced by test.sh.
#
# The allowed list comes from a "// ALLOWED_FUNCTIONS: write" comment at
# the top of the exercise's own mini-moul test file (empty = None).
#
# Heuristic, not a real parser: strips comments/strings via strip_c first,
# then greps for "name(" among a fixed list of restricted functions.
# Won't catch a function called only through a pointer, for example.

RESTRICTED_FUNCTIONS="printf fprintf sprintf snprintf vprintf vfprintf vsprintf vsnprintf puts putchar putw fputs fputc scanf fscanf sscanf gets fgets perror malloc calloc realloc free memcpy memmove memset memcmp strcpy strncpy strcat strncat strcmp strncmp strcasecmp strncasecmp strlen strdup strchr strrchr strstr strtok strtok_r strpbrk strspn strcspn strerror atoi atol atof strtol strtoul strtod itoa isalpha isdigit isalnum isspace isupper islower ispunct isprint iscntrl toupper tolower exit abort system popen pclose fork execve execvp wait waitpid open close read write lseek fopen fclose fread fwrite fflush fseek ftell unlink access qsort bsearch rand srand time basename"

# check_forbidden_functions <mini_moul_test_dir> <student_source_dir>
# Prints a space-separated list of forbidden function names found (empty
# if none), and any/all callers should treat a non-empty result as -42.
check_forbidden_functions()
{
    local test_dir="$1"
    local src_dir="$2"
    local allowed_raw
    local allowed_list
    local pattern
    local func
    local found=""
    local src
    local matches
    local is_allowed
    local a

    allowed_raw=$(grep -h -m1 "^// ALLOWED_FUNCTIONS:" "$test_dir"/*.c 2> /dev/null | sed 's/^\/\/ ALLOWED_FUNCTIONS://')
    allowed_list=$(echo "$allowed_raw" | tr ',' ' ')

    pattern=$(echo "$RESTRICTED_FUNCTIONS" | tr ' ' '\n' | paste -sd '|' -)

    # Most exercises' mini-moul test #includes one specific exercise file
    # by name (e.g. ".../ex04/ft_list_push_back.c") - that's the one file
    # the subject actually asks for, so only scan that one. A student's
    # directory can otherwise contain a legitimate local copy of an
    # earlier exercise's deliverable (e.g. ft_create_elem.c dropped into
    # ex04/ so the folder compiles standalone), which isn't part of what
    # ex04 itself is graded on and shouldn't be scanned for it.
    # Program-style exercises (do-op, libft, C10's CLI tools, ...) have no
    # such #include - their test builds every .c file with a wildcard -
    # so fall back to scanning everything in that case.
    local included_name
    included_name=$(grep -hoE '#include "(\.\./)+ex[0-9]+/[^"]+\.c"' "$test_dir"/*.c 2> /dev/null | head -n1 | grep -oE '[^/]+\.c"$' | tr -d '"')

    # Some exercises turn in only a header (C08's macro/struct exercises:
    # "Files to turn in : ft_boolean.h"). Their mini-moul test either
    # #includes that header directly, or -I's the student's directory to
    # compile a fixture written from the subject's own example program -
    # either way the student's .c file (if any is even present) is their
    # own local scratch/demo copy, never compiled by the test, and
    # shouldn't be scanned.
    local included_header
    included_header=$(grep -hoE '#include "(\.\./)+ex[0-9]+/[^"]+\.h"' "$test_dir"/*.c 2> /dev/null | head -n1 | grep -oE '[^/]+\.h"$' | tr -d '"')

    # Program-style exercises (do-op, C10's CLI tools, ...) build every .c
    # file in the student's directory via make or a wildcard cc - that's
    # real evidence their .c files are the graded deliverable.
    local wildcard_build=0
    if grep -qE '(\*\.c|make[[:space:]]+-C)' "$test_dir"/*.c 2> /dev/null; then
        wildcard_build=1
    fi

    local src_files
    if [ -n "$included_name" ] && [ -e "$src_dir/$included_name" ]; then
        src_files="$src_dir/$included_name"
    elif [ -n "$included_header" ] && [ -e "$src_dir/$included_header" ]; then
        src_files="$src_dir/$included_header"
    elif [ "$wildcard_build" = "0" ] && ls "$src_dir"/*.h > /dev/null 2>&1; then
        src_files="$src_dir"/*.h
    else
        src_files="$src_dir"/*.c
    fi

    for src in $src_files; do
        [ -e "$src" ] || continue
        matches=$("$UTILS_DIR/strip_c" < "$src" | grep -oE "\b(${pattern})[[:space:]]*\(" | sed -E 's/[[:space:]]*\(//')
        for func in $matches; do
            is_allowed=0
            for a in $allowed_list; do
                if [ "$a" = "$func" ]; then
                    is_allowed=1
                    break
                fi
            done
            if [ "$is_allowed" = "0" ]; then
                case " $found " in
                    *" $func "*) ;;
                    *) found="$found $func" ;;
                esac
            fi
        done
    done

    echo "$found" | xargs -n1 2>/dev/null | sort -u | xargs
}
