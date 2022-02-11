#!/usr/bin/env bash

set -euo pipefail

contain() {
  declare -n array=$1
  declare val=$2
  for elem in "${array[@]}"; do
    if [[ "$elem" == "$val" ]]; then
      return 0
    fi
  done
  return 1
}

#shellcheck disable=SC2034
KEYS=(a b key value)

read-config() {
  while read -r line; do
    local key="${line%%=*}"
    local value="${line#*=}"
    if contain KEYS "$key"; then
      eval "declare -g $key=$value"
    else
      echo >&2 "Unrecognized key: $key"
    fi
  done <<EOF
a=1
b=2
key=value
value=key
EOF
}

read-config
echo "$a $b $key $value"
