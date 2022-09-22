#!/usr/bin/env bash

set -euo pipefail
# shellcheck disable=SC2034
SCRIPT_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)

readarray -t array < <(echo "asdf" | grep -o .)

echo "${#array[@]}"
