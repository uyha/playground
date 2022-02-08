#!/usr/bin/env bash

while IFS="<newline>" read -r value; do
  echo "$value"
done < <(find . -type f)
