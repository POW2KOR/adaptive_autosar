#!/bin/sh

set -eux

/sbin/amsr_vector_fs_em_executionmanager -a /opt -m /etc/machine_exec_config.json
