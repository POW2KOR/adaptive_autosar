#!/bin/bash

echo "Pre-removal script: stop and disable the adaptive stack and ipv6 loopback..."
# stop the services
sudo systemctl stop adaptive-stack
sudo systemctl stop enable-ipv6-loopback
# disable the services
sudo systemctl disable adaptive-stack
sudo systemctl disable enable-ipv6-loopback


echo "Pre-removal script: deleting the service files..."
sudo rm /lib/systemd/system/adaptive-stack.service
sudo rm /lib/systemd/system/enable-ipv6-loopback.service

echo "Pre-removal script: done!"
