#!/usr/bin/env bash

array=(1 2 3a)
array+=(4 5 6)

if [[ 5 == "${array[-1]}" ]]; then
  echo 1
fi

array=("${array[@]/#/\"}")
array=("${array[@]/%/\"}")

echo "${array[@]}"
