#!/usr/bin/env bash

set -euo pipefail
# shellcheck disable=SC2034
SCRIPT_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)

# a1=(1 2 3 4)
a2=("${a2[@]}")

echo "${#a2[@]}"
