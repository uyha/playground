#!/usr/bin/env bash

# set -euo pipefail

#shellcheck disable=SC2034
SCRIPT_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)

a="$(perl -pe 's/\n//' </home/uy/.config/rclone/rclone.conf)"
b="$(rclone backend -o config drives wdrive: | perl -pe 's/\[AllDrives\]/[shared_drives]/' | perl -pe 's/\n//')"

if [[ "$a" =~ .*"$b".* ]]; then
  echo matched
else
  echo nope
fi
