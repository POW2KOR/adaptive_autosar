#!/bin/bash
# A simple shell script to delete all Bridge networks

set -e

sudo ip link show | grep br- | awk -F ':' '{print $2}' | tr -d ' ' | while read b; do sudo ip link set "$b" down; sudo brctl delbr "$b"; done
