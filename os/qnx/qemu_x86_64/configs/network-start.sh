#!/bin/sh

# Start networking manager with e1000 driver
io-pkt-v6-hc -de1000

if_up -p wm0
ifconfig wm0 10.10.1.11/16
ifconfig wm0 ip4csum tcp4csum udp4csum tcp6csum-tx udp6csum-tx tso4

if_up -p wm1
ifconfig wm1 10.1.17.98/16
ifconfig wm1 ip4csum tcp4csum udp4csum tcp6csum-tx udp6csum-tx tso4

# Create vlan10 interfaces
ifconfig vlan10 create
ifconfig vlan10 vlan 10 vlanif wm0
ifconfig vlan10 10.10.1.90 netmask 255.255.0.0 up
ifconfig vlan10 239.10.0.2 netmask 255.255.0.0 alias

# Create vlan127 interfaces
ifconfig vlan127 create
ifconfig vlan127 vlan 127 vlanif wm0
ifconfig vlan127 10.127.1.90 netmask 255.255.0.0 up
ifconfig vlan127 239.127.0.2 netmask 255.255.0.0 alias

