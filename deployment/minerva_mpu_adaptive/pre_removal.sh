#!/bin/bash

echo "Pre-removal script: stop and disable the adaptive stack and network configuration..."
# Delete network configuration
sudo /usr/share/minerva/network_setup.sh -i eth0 -d

# stop the services
sudo systemctl stop adaptive-stack
sudo systemctl stop adaptive-network-config
# disable the services
sudo systemctl disable adaptive-stack
sudo systemctl disable adaptive-network-config


echo "Pre-removal script: deleting the service files..."
sudo rm /lib/systemd/system/adaptive-stack.service
sudo rm /lib/systemd/system/adaptive-network-config.service

echo "Pre-removal script: done!"
