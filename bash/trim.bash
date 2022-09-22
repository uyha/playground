#!/usr/bin/env bash

set -euo pipefail
# shellcheck disable=SC2034
SCRIPT_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)

echo " tar.gz          " | perl -pe 's/^\s*(.*?)\s*$/\1/' | wc
