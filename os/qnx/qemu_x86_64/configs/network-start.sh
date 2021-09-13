#!/bin/sh

# Start networking manager with e1000 driver
io-pkt-v6-hc -de1000

if_up -p wm0
ifconfig wm0 172.16.10.107
ifconfig wm0 ip4csum tcp4csum udp4csum tcp6csum-tx udp6csum-tx tso4

# Create vlan10 interfaces
ifconfig vlan10 create
ifconfig vlan10 vlan 10 vlanif wm0
ifconfig vlan10 10.10.1.90 netmask 255.255.0.0 up
ifconfig vlan10 239.10.0.2 netmask 255.255.0.0 alias
ifconfig vlan10 239.10.0.3 netmask 255.255.0.0 alias

# Create vlan127 interfaces
ifconfig vlan127 create
ifconfig vlan127 vlan 127 vlanif wm0
ifconfig vlan127 10.127.1.90 netmask 255.255.0.0 up
ifconfig vlan127 239.127.0.2 netmask 255.255.0.0 alias
ifconfig vlan127 239.127.0.3 netmask 255.255.0.0 alias

# Create vlan210 interfaces
ifconfig vlan210 create
ifconfig vlan210 vlan 210 vlanif wm0
ifconfig vlan210 10.210.220.2 netmask 255.255.255.240 up
ifconfig vlan210 239.210.224.245 netmask 255.255.0.0 alias
ifconfig vlan210 239.210.224.1 netmask 255.255.0.0 alias

# Create vlan21 interfaces
ifconfig vlan21 create
ifconfig vlan21 vlan 21 vlanif wm0
ifconfig vlan21 10.21.17.98 netmask 255.255.0.0 up

