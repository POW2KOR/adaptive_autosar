package(default_visibility = ["//visibility:public"])

genrule(
    name = "build_collectd",
    srcs =  ["@collectd_mbient//:all_files"],
    outs = [
        "output_log.txt"
    ],
    cmd = """ 
        set -x
        cd external/collectd_mbient

        autoheader
        aclocal -I m4
        libtoolize --copy --force 
        automake --add-missing --copy
        autoconf

        ./configure --host x86_64-ubuntu-linux-gnu --disable-all-plugins \
            --prefix $$(pwd)/../../collectd_artifacts \
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
        tree . >> ../../$@
        make install  
        """
)
