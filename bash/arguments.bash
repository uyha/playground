#!/usr/bin/env bash

set -euo pipefail

#shellcheck disable=SC2034
SCRIPT_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)

echo "$@"
echo "$#"

current=-"${1:2}"
shift 1
set -- "$current" "$@"

echo "$@"
echo "$#"
