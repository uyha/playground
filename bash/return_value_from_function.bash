#!/usr/bin/env bash

set -e

return-true(){
  true
}

return-false(){
  false
}

echo "Will be printed"
false
echo "Won't be printed"
