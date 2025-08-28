#!/bin/bash

source ~/mini-moulinette/mini-moul/config.sh
# assignment name
assignment=NULL

function handle_sigint {
  echo "${RED}Script aborted by user. Cleaning up..."
  rm -R ../mini-moul
  echo ""
  echo "${GREEN}Cleaning process done.${DEFAULT}"
  exit 1
}

# Function to determine if current directory matches a pattern
detect_assignment() {
  local dir_name=$(basename "$(pwd)")
  # Extract assignment pattern from directory name (e.g., C00, C01, etc.)
  if [[ $dir_name =~ C(0[0-9]|1[0-3]) ]]; then
    assignment="${BASH_REMATCH[0]}"
    return 0
  fi
  return 1
}

# Check if assignment was provided as argument
if [[ -n "$1" && $1 =~ ^C(0[0-9]|1[0-3])$ ]]; then
  assignment="$1"
elif detect_assignment; then
  # assignment already set by detect_assignment function
  :
else
  printf "${RED}Could not detect assignment from directory name and no valid assignment provided.${DEFAULT}\n"
  printf "${RED}Usage: mini [C00-C13] or run from a directory containing C00-C13 pattern.${DEFAULT}\n"
  printf "${RED}Examples: mini C00, or run from directory like 'git_C00', 'TestingC01', 'C02_Name'${DEFAULT}\n"
  exit 1
fi

cp -R ~/mini-moulinette/mini-moul mini-moul
if command -v norminette &> /dev/null; then
	norminette $(ls | grep -v 'mini-moul')
else
	echo "norminette not found, skipping norminette checks"
fi
trap handle_sigint SIGINT
cd mini-moul
./test.sh "$assignment"
rm -R ../mini-moul

exit 1
