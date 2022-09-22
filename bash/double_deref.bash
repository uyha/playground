#!/usr/bin/env bash

set -euo pipefail

bin=(a b c)
completions=(a b r)
declare -a bindings

for dir in bin completions bindings; do
  if [[ -z ${!dir+z} ]]; then
    continue
  fi
  declare -n ref="$dir"
  if [[ "${#ref[@]}" -gt 0 ]]; then
    echo "${ref[@]}"
  fi
done
