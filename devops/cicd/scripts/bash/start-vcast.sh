#!/bin/bash
# Usage:unencrypt.sh<passphrase><release_archive>


#Update the .lic file to the latest version and the location where it will get downloaded
cd /usr/tools/vcast/
./flexlm/lmgrd -c ./vector-IP-10-101-1-166.lic -l logs.txt
sleep 5s

./flexlm/lmutil lmstat
./vcshell --version
