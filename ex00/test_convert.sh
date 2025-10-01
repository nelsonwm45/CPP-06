#!/usr/bin/env bash
# Simple test harness for CPP06 ex00 "convert"
# Usage: bash test_convert.sh [path_to_convert]
# Default binary is ./convert

set -u

BIN="${1:-./convert}"
if [ ! -x "$BIN" ]; then
  echo "Error: '$BIN' not found or not executable."
  echo "Usage: bash $0 ./convert"
  exit 1
fi

# Pretty colors (fallback if not TTY)
if [ -t 1 ]; then
  GREEN="$(printf '\033[32m')"
  RED="$(printf '\033[31m')"
  CYAN="$(printf '\033[36m')"
  BOLD="$(printf '\033[1m')"
  RESET="$(printf '\033[0m')"
else
  GREEN=""; RED=""; CYAN=""; BOLD=""; RESET=""
fi

# Each test line: input|||expected_substring_1;;;expected_substring_2;;;expected_substring_3...
# Keep assertions fuzzy to allow minor formatting differences while still checking the spirit.
read -r -d '' TESTS <<'EOF'
0|||char: Non displayable;;;int: 0;;;float: 0.0f;;;double: 0.0
nan|||char: impossible;;;int: impossible;;;float: nanf;;;double: nan
42.0f|||char: '*';;;int: 42;;;float: 42.0f;;;double: 42.0
a|||char: 'a';;;int: 97
A|||char: 'A';;;int: 65
-42|||char: impossible;;;int: -42;;;float: -42.0f;;;double: -42.0
-4.2f|||char: impossible;;;int: -4;;;float: -4.2f;;;double: -4.2
4.2|||char: Non displayable;;;int: 4;;;float: 4.2f;;;double: 4.2
+inf|||char: impossible;;;int: impossible;;;float: +inff;;;double: +inf
-inf|||char: impossible;;;int: impossible;;;float: -inff;;;double: -inf
+inff|||char: impossible;;;int: impossible;;;float: +inff;;;double: +inf
-inff|||char: impossible;;;int: impossible;;;float: -inff;;;double: -inf
2147483647|||char: impossible;;;int: 2147483647;;;double: 2147483647.0
2147483648|||char: impossible;;;int: impossible;;;float: impossible;;;double: impossible
127|||char: Non displayable;;;int: 127
128|||char: impossible;;;int: 128;;;float: 128.0f;;;double: 128.0
EOF


total=0
passed=0

echo "${BOLD}Running tests against: $BIN${RESET}"
echo

while IFS= read -r line; do
  # skip empty
  [ -z "$line" ] && continue

  input="${line%%|||*}"
  rest="${line#*|||}"

  # Split expected substrings by ';;;' safely
  IFS=';;;' read -r -a expects <<< "$rest"

  total=$((total + 1))
  echo "${CYAN}[$total] Input:${RESET} $input"
  output="$("$BIN" "$input" 2>&1)"
  status=$?

  # Show the program output
  echo "----- output begin -----"
  echo "$output"
  echo "------ output end ------"

  # Basic sanity: program should exit 0 (adjust if your program uses non-zero for errors)
  if [ $status -ne 0 ]; then
    echo "${RED}FAIL${RESET} (exit code $status)"
    echo
    continue
  fi

  # Check all expected substrings are present
  ok=1
  for exp in "${expects[@]}"; do
    # Allow blank exp slots (when a test case wants fewer checks)
    [ -z "$exp" ] && continue
    # Use grep -F for literal match to avoid regex surprises
    echo "$output" | grep -F -- "$exp" >/dev/null 2>&1
    if [ $? -ne 0 ]; then
      echo "${RED}Missing:${RESET} $exp"
      ok=0
    fi
  done

  if [ $ok -eq 1 ]; then
    echo "${GREEN}PASS${RESET}"
    passed=$((passed + 1))
  else
    echo "${RED}FAIL${RESET}"
  fi

  echo
done <<< "$TESTS"

echo "${BOLD}Summary:${RESET} $passed / $total passed"
# Return non-zero if any test failed (useful for CI)
[ $passed -eq $total ]
