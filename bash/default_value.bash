#!/usr/bin/env bash

set -euo pipefail

#shellcheck disable=SC2034
SCRIPT_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)

func(){
  a="${1:-3}"
  echo "$a"
}

func
func 2

