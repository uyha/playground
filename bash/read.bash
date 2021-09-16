while IFS="<newline>" read value; do
  echo "$value"
done < <(find . -type f)
