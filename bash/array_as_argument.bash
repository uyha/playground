#!/usr/bin/env bash

set -euo pipefail

fn() {
  declare -n arr=$1
  echo "${arr[@]}"
}

#shellcheck disable=SC2034
a=(1 2 3 4)
fn a
