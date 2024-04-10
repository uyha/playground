#!/usr/bin/env bash

set -euo pipefail

#shellcheck disable=SC2034
SCRIPT_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)

echo "$@"
echo "$1"

set -- "-${1:1}" "${@:2}"

echo "$@"
echo "$1"
