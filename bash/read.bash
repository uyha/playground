#!/usr/bin/env bash

while read -r value; do
  wc -c <<<"$value"
done <<EOF
  a aa aaa   
EOF
