#!/usr/bin/env bash

array=(1 2 3)
array+=(4 5 6)

if [[ 5 == "${array[-1]}" ]]; then
  echo 1
fi
