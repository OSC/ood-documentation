# Scan all pages
find /doc/build/html -name "*.html" | while read f; do
  result=$(pa11y-ci "$f")
  exit_code=$?

  if echo "$result" | grep -q "Error:"; then
    echo "--- $f ---"
    echo "$result" | grep -A2 "Error:"
  fi

  if [ $exit_code -ne 0 ]; then
    echo "pa11y-ci encountered an error on $f (exit code $exit_code). Stopping scan."
    exit 1
  fi
  echo -n "$result"
done | tee pa11y-report.txt | echo ''