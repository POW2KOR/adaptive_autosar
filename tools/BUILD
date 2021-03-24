package(default_visibility = ["//visibility:public"])

genrule(
    name = "build_collectd",
    srcs = ["@collectd_mbient//:all_files"],
    outs = [
        "share/perl/5.26.1/Collectd/Plugins/OpenVZ.pm",
        "share/perl/5.26.1/Collectd/Unixsock.pm",
        "share/perl/5.26.1/Collectd.pm",
        "share/collectd/java/collectd-api.jar",
        "share/collectd/java/generic-jmx.jar",
        "share/collectd/postgresql_default.conf",
        "share/collectd/types.db",
        "lib/x86_64-linux-gnu/perl/5.26.1/auto/Collectd/.packlist",
        "lib/x86_64-linux-gnu/perl/5.26.1/perllocal.pod",
        "lib/libcollectdclient.la",
        "lib/collectd/match_regex.so",
        "lib/collectd/entropy.so",
        "lib/collectd/interface.so",
        "lib/collectd/ethstat.la",
        "lib/collectd/match_empty_counter.so",
        "lib/collectd/contextswitch.so",
        "lib/collectd/load.so",
        "lib/collectd/buddyinfo.so",
        "lib/collectd/match_value.la",
        "lib/collectd/unixsock.so",
        "lib/collectd/interface.la",
        "lib/collectd/match_value.so",
        "lib/collectd/load.la",
        "lib/collectd/disk.la",
        "lib/collectd/contextswitch.la",
        "lib/collectd/memory.so",
        "lib/collectd/match_empty_counter.la",
        "lib/collectd/df.la",
        "lib/collectd/unixsock.la",
        "lib/collectd/cpu.la",
        "lib/collectd/cgroups.la",
        "lib/collectd/ethstat.so",
        "lib/collectd/df.so",
        "lib/collectd/write_log.so",
        "lib/collectd/write_log.la",
        "lib/collectd/irq.la",
        "lib/collectd/irq.so",
        "lib/collectd/cgroups.so",
        "lib/collectd/logfile.so",
        "lib/collectd/logfile.la",
        "lib/collectd/processes.so",
        "lib/collectd/vmem.la",
        "lib/collectd/rrdtool.la",
        "lib/collectd/write_graphite.la",
        "lib/collectd/csv.so",
        "lib/collectd/entropy.la",
        "lib/collectd/cpu.so",
        "lib/collectd/rrdtool.so",
        "lib/collectd/match_regex.la",
        "lib/collectd/buddyinfo.la",
        "lib/collectd/gps.la",
        "lib/collectd/gps.so",
        "lib/collectd/memory.la",
        "lib/collectd/csv.la",
        "lib/collectd/disk.so",
        "lib/collectd/write_graphite.so",
        "lib/collectd/processes.la",
        "lib/collectd/vmem.so",
        "lib/pkgconfig/libcollectdclient.pc",
        "lib/libcollectdclient.so.1.1.0",
        "include/collectd/network.h",
        "include/collectd/network_parse.h",
        "include/collectd/client.h",
        "include/collectd/lcc_features.h",
        "include/collectd/network_buffer.h",
        "include/collectd/server.h",
        "include/collectd/types.h",
        "bin/collectdctl",
        "bin/collectd-tg",
        "bin/collectd-nagios",
        "etc/collectd.conf",
        #"man/man3/Collectd::Unixsock.3pm",
        "sbin/collectdmon",
        "sbin/collectd",
    ],
    cmd = """ 
        set -e -o pipefail
        set -x
        cd external/collectd_mbient

        autoheader
        aclocal -I m4
        libtoolize --copy --force 
        automake --add-missing --copy
        autoconf

        ./configure --host x86_64-ubuntu-linux-gnu --disable-all-plugins \
            --prefix $$(pwd)/../../bazel-out/k8-fastbuild/bin/tools \
            --disable-java \
            --disable-perl \
            --enable-cpu \
            --enable-csv \
            --enable-buddyinfo \
            --enable-cgroups \
            --enable-contextswitch \
            --enable-df \
            --enable-disk \
            --enable-entropy \
            --enable-ethstat \
            --enable-interface \
            --enable-irq \
            --enable-load \
            --enable-logfile \
            --enable-match_empty_counter \
            --enable-match_regex \
            --enable-match_value \
            --enable-memory \
            --enable-processes \
            --enable-rrdtool \
            --enable-unixsock \
            --enable-vmem \
            --enable-write_graphite  \
            --enable-write_log \
            --enable-gps
        
        make all
        make install  
        """,
)
