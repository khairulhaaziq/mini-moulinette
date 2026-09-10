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

run_norminette() {
  if command -v norminette &> /dev/null; then
    # exclude the freshly-copied mini-moul/ folder itself: it doesn't
    # follow the Norm and was never meant to be checked against it
    norminette $(ls | grep -v '^mini-moul$')
  else
    echo "norminette not found, skipping norminette checks"
  fi
}

# Function to determine if current directory matches a pattern
# (accepts lowercase folder names too, e.g. c00, c01, ...)
detect_assignment() {
  local dir_name
  local upper_name
  dir_name=$(basename "$(pwd)")
  upper_name=$(echo "$dir_name" | tr '[:lower:]' '[:upper:]')
  if [[ $upper_name =~ ^C(0[0-9]|1[0-3])$ ]]; then
    assignment="$upper_name"
    return 0
  fi
  return 1
}

if detect_assignment; then
  cp -R ~/mini-moulinette/mini-moul mini-moul
  run_norminette
  trap handle_sigint SIGINT
  cd mini-moul
  ./test.sh "$assignment"
  test_status=$?
  cd ..
  rm -R mini-moul
  exit $test_status
else
  printf "${RED}Current directory does not match expected pattern (C[00~13]).${DEFAULT}\n"
  printf "${RED}Please navigate to an appropriate directory to run tests.${DEFAULT}\n"
  exit 1
fi
