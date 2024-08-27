#!/usr/bin/env bash

set -euo pipefail

#shellcheck disable=SC2034
SCRIPT_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)

declare -A arr
arr[a]=$((${arr[a]:-0} + 1))
arr[a]=$((${arr[a]:-0} + 1))
echo "${arr[a]}"
