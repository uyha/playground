#!/usr/bin/env bash

set -euo pipefail
# shellcheck disable=SC2034
SCRIPT_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)

a=1234

if echo "$a" | perl -ne 'exit not(/\d{4}/)'; then
  echo "yeah"
fi
