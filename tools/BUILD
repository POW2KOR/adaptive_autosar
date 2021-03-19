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
            --disable-java \
            --disable-perl \
            --enable-cpu
        
        make all
        make install
        """
)