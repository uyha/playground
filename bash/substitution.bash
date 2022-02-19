#!/usr/bin/env bash

set -euo pipefail

a=(1 2 3)
a=("${a[@]/#/asdf}")
a=("${a[@]/%/end}")

echo "${a[@]}"


