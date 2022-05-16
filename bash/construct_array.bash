#!/usr/bin/env bash

array_string="1 2"
#shellcheck disable=SC2206
array=($array_string)

echo "${array[@]}"
echo $((("${array[0]}" << 4) | ("${array[1]}" >> 4)))
