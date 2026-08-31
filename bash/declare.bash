#!/usr/bin/env bash

set -euo pipefail

contains() {
  declare -n haystack
  haystack=$1
  needle=$2

  for item in "${haystack[@]}"; do
    if [[ "${needle}" == "${item}" ]]; then return 0; fi
  done

  false
}

array=(1 2 3)
if contains array 3; then
  echo yes
else
  echo no
fi
