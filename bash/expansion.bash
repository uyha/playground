#!/usr/bin/env bash

set -euo pipefail

root="${root:-/opt}"
install_dir="${install_dir:-$root/local}"

echo "$root $install_dir"
