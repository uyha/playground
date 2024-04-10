#!/usr/bin/env bash

set -euo pipefail

positional_args=()
while [[ $# -gt 0 ]]; do
  case "$1" in
  --prefix | -p)
    prefix=$2
    shift 2
    ;;
  --prefix=*)
    prefix="${1#--prefix=}"
    shift 1
    ;;
  -p=*)
    prefix="${1#-p=}"
    shift 1
    ;;
  -p*)
    prefix="${1#-p}"
    shift 1
    ;;
  --case | -c)
    case=$2
    shift 2
    ;;
  --case=*)
    case="${1#--case=}"
    shift 1
    ;;
  -c=*)
    case="${1#-c=}"
    shift 1
    ;;
  -c*)
    case="${1#-c}"
    shift 1
    ;;
  -s)
    count=$((${count:-0} + 1))
    shift 1
    ;;
  -s*)
    count=$((${count:-0} + 1))
    set -- "-${1:2}" "${@:2}"
    ;;
  esac
done

echo "prefix: ${prefix:-}"
echo "case: ${case:-}"
echo "${count:=0}"
