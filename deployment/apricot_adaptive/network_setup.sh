#!/bin/sh
# Script taken from Starter Kit Adaptive Application.

INTERFACE=
COMPANY=
IF_SHORT_ALIAS=
INTERFACE_CREATED=0
VALIDITY=
NETWORK_FILE="/var/run/apricot_net_info"

# Print help message
print_helper() {
    echo 'Help: '
    echo 'Legal options are '
    echo '-h        : print this helper'
    echo '-m        : Mercedes Benz AG laptop firewall settings'
    echo '-i  $name : Use interface $name for the setup'
    echo '-a  $name : Use an arbitrary short alias $name for the interface. Might be necessary, if the interface extends 11 characters'
    echo '-d        : Delete network configuration saved under "/var/run/apricot_mpu_net_info"'

    exit 0
}

# Fuction to cleanup Network configuration
clean_net_cfg() {
    echo "Cleanup network config"
    if [ ! -f $NETWORK_FILE ]; then
        echo "Error: file '$NETWORK_FILE' not found!"
        exit 1;
    fi
    # Read file
    while read net_name; do
        if ip link del $net_name > /dev/null 2>&1; then
            echo "Deleted existing network $net_name"
        else
            echo "Network $net_name was not found."
        fi
    done < $NETWORK_FILE
    rm -f $NETWORK_FILE

    if ping -c1 -w3 169.254.17.7 >/dev/null 2>&1
    then
        sudo ip addr del 169.254.17.7/16 dev $INTERFACE
    fi
}

# Doing some option cleanup using getopt:
while getopts hmi:a:d opt
do
    case $opt in
        h)
            print_helper
            ;;
        m)
            COMPANY=MBAG
            ;;
        i)
            if [ -z "$OPTARG" ] ; then
                echo 'Please define the network interface to use'
                print_helper
            fi
            INTERFACE=$OPTARG
            VALIDITY=1
            ;;
        a)
            if [ -z "$OPTARG" ] ; then
                echo 'Please define an arbitrary short alias for the interface'
                print_helper
            fi
            IF_SHORT_ALIAS=$OPTARG
            ;;
        d)
            # Delete VLANs
            clean_net_cfg;
            exit 0
            ;;
    esac
done

if [ -z "$IF_SHORT_ALIAS" ] ; then
    # Use Interface name if no specific alias is given
    IF_SHORT_ALIAS=$INTERFACE
fi

if [ ${#IF_SHORT_ALIAS} -gt 11 ]; then
    echo "Short interface alias ${IF_SHORT_ALIAS} might be too long. Consider specifying a shorter alias"
fi

echo 'Got following config'
echo "Interface:             ($INTERFACE)"
echo "Short interface alias: ($IF_SHORT_ALIAS)"
if [ ! -z "$COMPANY" ] ; then
    echo 'Company setting is Mercedes Benz AG'
fi
if [ -z "$VALIDITY" ] ; then
    echo 'Not a valid setup!!!'
    echo 'See manual:'
    print_helper
fi

if [ -z "$INTERFACE" ]; then
    echo 'Please define the network interface to use'
    exit 1
fi

ip addr show  | grep 'inet 10.20.1.113'
if [ $? -eq 0 ]; then
   echo 'IP address 10.20.1.113 found. Please check if sombody else is executing the stack on the system already'
else
    ip addr show $INTERFACE
    if [ $? -ne 0 ]; then
        echo "Network interface $INTERFACE not found. Network interface will be created"
        INTERFACE_CREATED=1
        # Setup Network for Proxy Skeleton Example
        sudo ip link add $INTERFACE type dummy
        sudo ip link set up $INTERFACE
    fi

    sudo ip link add link $INTERFACE name ${IF_SHORT_ALIAS}.1 type vlan id 1
    sudo ip link set up ${IF_SHORT_ALIAS}.1
    sudo ip addr add 10.1.17.99/16 dev ${IF_SHORT_ALIAS}.1
    sudo ip addr add 169.254.18.98/16 dev ${IF_SHORT_ALIAS}.1
    echo "${IF_SHORT_ALIAS}.1" >> $NETWORK_FILE

    sudo ip link add link $INTERFACE name ${IF_SHORT_ALIAS}.20 type vlan id 20
    sudo ip link set up ${IF_SHORT_ALIAS}.20
    sudo ip addr add 10.20.1.113/16 dev ${IF_SHORT_ALIAS}.20
    if [ $INTERFACE = "scale" ]; then
        sudo ip addr add 10.20.1.110/16 dev ${IF_SHORT_ALIAS}.20
        sudo ip addr add 10.20.1.111/16 dev ${IF_SHORT_ALIAS}.20
        sudo ip addr add 10.210.220.2/16 dev ${IF_SHORT_ALIAS}.20
    fi
    echo "${IF_SHORT_ALIAS}.20" >> $NETWORK_FILE

    sudo ip link add link $INTERFACE name ${IF_SHORT_ALIAS}.21 type vlan id 21
    sudo ip link set up ${IF_SHORT_ALIAS}.21
    sudo ip addr add 10.21.17.98/16 dev ${IF_SHORT_ALIAS}.21
    echo "${IF_SHORT_ALIAS}.21" >> $NETWORK_FILE

    sudo ip link add link $INTERFACE name ${IF_SHORT_ALIAS}.127 type vlan id 127
    sudo ip link set up ${IF_SHORT_ALIAS}.127
    sudo ip addr add 10.127.17.98/16 dev ${IF_SHORT_ALIAS}.127
    sudo ip addr add 10.127.1.90/16 dev ${IF_SHORT_ALIAS}.127
    echo "${IF_SHORT_ALIAS}.127" >> $NETWORK_FILE

    sudo ip link add link $INTERFACE name ${IF_SHORT_ALIAS}.10 type vlan id 10
    sudo ip link set up ${IF_SHORT_ALIAS}.10
    sudo ip addr add 10.10.1.90/16 dev ${IF_SHORT_ALIAS}.10
    #sudo ip addr add 10.10.1.113/16 dev ${IF_SHORT_ALIAS}.10
    sudo ip addr add 239.10.0.2/16 dev ${IF_SHORT_ALIAS}.10
    echo "${IF_SHORT_ALIAS}.19" >> $NETWORK_FILE
    if [ $INTERFACE = "scale" ]; then
        sudo ip addr add 10.10.1.90/16 dev ${IF_SHORT_ALIAS}.10
    fi

    sudo ip link add link $INTERFACE name ${IF_SHORT_ALIAS}.210 type vlan id 210
    sudo ip link set up ${IF_SHORT_ALIAS}.210
    sudo ip addr add 10.210.220.3/16 dev ${IF_SHORT_ALIAS}.210
    sudo ip addr add 10.210.220.2/16 dev ${IF_SHORT_ALIAS}.210
    sudo ip addr add 239.210.224.245/16 dev ${IF_SHORT_ALIAS}.210
    echo "${IF_SHORT_ALIAS}.210" >> $NETWORK_FILE

    if [ $INTERFACE_CREATED -eq 1 ]; then
        echo "$INTERFACE" >> $NETWORK_FILE
    fi

    # Diagnostic IP-Address
    sudo ip addr add 169.254.17.7/16 dev $INTERFACE

    # Setup Network for IPC-Communication via ara::com
    sudo ip link set lo multicast on
    sudo ip route add ff01::0/16 dev lo

    if [ "$COMPANY" = "MBAG" ]; then
        echo 'MBAG Notebook expected. Setting Mercedes Benz AG special firewall settings'

        # Disable firewall on devices used for communication
        sudo firewall-cmd --zone=trusted --add-interface=lo
        sudo firewall-cmd --zone=trusted --add-interface=$INTERFACE
        sudo firewall-cmd --zone=trusted --add-interface=${IF_SHORT_ALIAS}.1
        sudo firewall-cmd --zone=trusted --add-interface=${IF_SHORT_ALIAS}.20
        sudo firewall-cmd --zone=trusted --add-interface=${IF_SHORT_ALIAS}.21
        sudo firewall-cmd --zone=trusted --add-interface=${IF_SHORT_ALIAS}.127
        sudo firewall-cmd --zone=trusted --add-interface=${IF_SHORT_ALIAS}.10
        sudo firewall-cmd --zone=trusted --add-interface=${IF_SHORT_ALIAS}.210
    fi
fi
