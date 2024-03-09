#!/usr/bin/env bash

set -euo pipefail

#shellcheck disable=SC2034
SCRIPT_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)

cat <(
  echo "1;"
  head /dev/random -n1
  echo 2
)
