#!/usr/bin/env bash

function fn(){
  sleep 5
  echo "Finished"
}

fn &

echo $!

