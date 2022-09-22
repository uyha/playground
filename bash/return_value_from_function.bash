#!/usr/bin/env bash

set -e

return-1() {
  return 1
}

return-0() {
  return 0
}

return-true() {
  true
}

return-false() {
  false
}

echo "Will be printed"
return-0
echo "Won't be printed"
