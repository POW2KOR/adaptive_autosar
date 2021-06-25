#!/bin/sh

# Start networking manager with virtio driver
io-pkt-v6-hc -dvirtio

if_up -p vt0
ifconfig vt0 10.1.17.98/16

if_up -p vt1
ifconfig vt1 10.20.17.98/16

if_up -p vt2
ifconfig vt2 10.21.17.98

if_up -p vt3
ifconfig vt3 10.127.17.98/16

if_up -p vt4
ifconfig vt4 10.20.1.98/16
