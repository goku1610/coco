#!/usr/bin/env bash
set -u
set -o pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

detect_original_dir() {
  local candidates=(
    "$ROOT_DIR/Compiler_Construction"
    "$ROOT_DIR/Compiler-Construction"
    "/home/saksham/coding/CoCoMelon/Compiler-Construction"
  )
  local d
  for d in "${candidates[@]}"; do
    if [[ -d "$d" ]]; then
      printf "%s" "$d"
      return 0
    fi
  done
  return 1
}

MERGED_DIR_DEFAULT="$ROOT_DIR/Compiler_Construction_Complete_Merged"
ORIG_DIR_DEFAULT="$(detect_original_dir 2>/dev/null || true)"

MERGED_DIR="${1:-$MERGED_DIR_DEFAULT}"
ORIG_DIR="${2:-$ORIG_DIR_DEFAULT}"
TEST_DIR="${3:-$MERGED_DIR/tests}"
OUT_CSV="${4:-$MERGED_DIR/reports/errors_comparison_all_tests.csv}"

if [[ -z "$ORIG_DIR" ]]; then
  echo "Error: Could not auto-detect original compiler directory."
  echo "Usage: $0 [merged_dir] [original_dir] [tests_dir] [output_csv]"
  exit 1
fi

if [[ ! -d "$MERGED_DIR" ]]; then
  echo "Error: merged directory not found: $MERGED_DIR"
  exit 1
fi
if [[ ! -d "$ORIG_DIR" ]]; then
  echo "Error: original directory not found: $ORIG_DIR"
  exit 1
fi
if [[ ! -d "$TEST_DIR" ]]; then
  echo "Error: tests directory not found: $TEST_DIR"
  exit 1
fi

mkdir -p "$(dirname "$OUT_CSV")"

echo "Building merged compiler: $MERGED_DIR"
(
  cd "$MERGED_DIR" || exit 1
  make >/dev/null
)
if [[ ! -x "$MERGED_DIR/stage1exe" ]]; then
  echo "Error: merged compiler executable missing after build: $MERGED_DIR/stage1exe"
  exit 1
fi

echo "Building original compiler: $ORIG_DIR"
(
  cd "$ORIG_DIR" || exit 1
  make >/dev/null
)
if [[ ! -x "$ORIG_DIR/stage1exe" ]]; then
  echo "Error: original compiler executable missing after build: $ORIG_DIR/stage1exe"
  exit 1
fi

echo "file,merged_status,merged_exit_code,merged_errors,original_status,original_exit_code,original_errors,errors_match" > "$OUT_CSV"

total_files=0
match_files=0
mismatch_files=0

while IFS= read -r testcase; do
  total_files=$((total_files + 1))
  base="$(basename "$testcase")"
  log_merged="$(mktemp)"
  log_orig="$(mktemp)"

  (
    cd "$MERGED_DIR" || exit 1
    ./stage1exe "$testcase" "_ignore_out.txt" > "$log_merged" 2>&1 <<< $'2\n0\n'
  ) 2>/dev/null
  merged_code=$?
  if [[ $merged_code -eq 0 ]]; then
    merged_status="ok"
  else
    merged_status="failed"
  fi
  merged_errors="$(grep -c 'Lexical Error:' "$log_merged" || true)"

  (
    cd "$ORIG_DIR" || exit 1
    ./stage1exe "$testcase" "_ignore_out.txt" > "$log_orig" 2>&1 <<< $'2\n0\n'
  ) 2>/dev/null
  orig_code=$?
  if [[ $orig_code -eq 0 ]]; then
    orig_status="ok"
  else
    orig_status="failed"
  fi
  orig_errors="$(grep -c 'Lexical Error:' "$log_orig" || true)"

  if [[ "$merged_errors" == "$orig_errors" ]]; then
    errors_match="true"
    match_files=$((match_files + 1))
  else
    errors_match="false"
    mismatch_files=$((mismatch_files + 1))
  fi

  echo "$base,$merged_status,$merged_code,$merged_errors,$orig_status,$orig_code,$orig_errors,$errors_match" >> "$OUT_CSV"

  rm -f "$log_merged" "$log_orig"
done < <(find "$TEST_DIR" -maxdepth 1 -type f -name '*.txt' | sort)

echo "Done."
echo "CSV: $OUT_CSV"
echo "Files compared: $total_files | matches: $match_files | mismatches: $mismatch_files"
