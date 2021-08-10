#!/bin/bash

echo "Post install script: copying the service files..."
sudo cp /usr/share/apricot/*.service /lib/systemd/system

echo "Post install script: enable and start the adaptive stack and ipv6 loopback..."
# enable the services, so that it will automatically start on boot
sudo systemctl enable adaptive-network-config
sudo systemctl enable adaptive-stack
# start the services
sudo systemctl start adaptive-network-config
sudo systemctl start adaptive-stack

echo "Post install script: done!"
