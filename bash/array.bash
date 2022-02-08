#!/usr/bin/env bash

array=(1 2 3)
array+=(4 5 6)

[[ "${array[*]}" =~ 8 ]] && echo 1
