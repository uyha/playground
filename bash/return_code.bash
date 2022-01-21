#!/usr/bin/env bash

exists() {
  command -v "$@" >/dev/null
}

if exists cp; then
  echo 1;
fi

if ! exists nothing-meaningful; then
  echo 2;
fi
