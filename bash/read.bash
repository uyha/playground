#!/usr/bin/env bash

while read -r value; do
  if [[ -z "$value" ]]; then continue; fi
  printf "%s" "$value" | wc -c
  printf "'%s'\n" "$value"
done <<EOF
  a aa aaa   
a  asdf

  a aa aaa   
EOF
