#!/usr/bin/env bash

set -euo pipefail
# shellcheck disable=SC2034
SCRIPT_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)

fn() (
  readarray -t array <<EOF
a
b
c
EOF
  echo "${array[@]}"
)

declare array
array="a"
echo "$array"
fn
echo "$array"
