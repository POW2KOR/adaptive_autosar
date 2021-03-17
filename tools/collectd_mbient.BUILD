package(default_visibility = ["//visibility:public"])

filegroup(
    name = "collectd_srcs",
    srcs = glob(["src/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "m4_files",
    srcs = glob(["m4/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "build_sh",
    srcs = ["build.sh"],
    visibility = ["//visibility:public"],
)

filegroup(
    name = "configure_file",
    srcs = [
        "configure.ac",
    ],
    visibility = ["//visibility:public"],
)

filegroup(
    name = "version_gen_sh",
    srcs = [
        "version-gen.sh",
    ],
    visibility = ["//visibility:public"],
)

filegroup(
    name = "makefile_am",
    srcs = [
        "Makefile.am",
    ],
    visibility = ["//visibility:public"],
)

genrule(
    name = "build_collectd",
    srcs =  [":build_sh"] 
        + [":configure_file"] 
        + [":version_gen_sh"]
        + [":makefile_am"]
        + [":collectd_srcs"]
        + [":m4_files"],
    outs = [
        "output_log.txt"
        #"Makefile",
        #"aclocal.m4",
        #"build-aux/ltmain.sh",
        #"m4/libtool.m4",
        #"m4/ltoptions.m4",
        #"m4/ltsugar.m4",
        #"m4/ltversion.m4",
        #"m4/lt~obsolete.m4",
        #"build-aux/compile",
        #"build-aux/config.guess",
        #"build-aux/config.sub",
        #"build-aux/install-sh",
        #"build-aux/missing",
        #"build-aux/depcomp",
        #"build-aux/ylwrap",
        #"build-aux/test-driver",
    ],
    cmd = """ 
        set -e -o pipefail
        cp $(location @collectd_mbient//:configure_file) .
        cp $(location @collectd_mbient//:version_gen_sh) .
        cp $(location @collectd_mbient//:makefile_am) .
        for file in $(locations @collectd_mbient//:collectd_srcs); do\
            mkdir -p $(RULEDIR)/$$(echo $$(dirname $$file) | cut -d'/' -f3-);\
            cp $$file $(RULEDIR)/$$(echo $$(dirname $$file) | cut -d'/' -f3-);\
            mkdir -p $$(echo $$(dirname $$file) | cut -d'/' -f3-);\
            cp $$file $$(echo $$(dirname $$file) | cut -d'/' -f3-);\
        done
        for file in $(locations @collectd_mbient//:m4_files); do\
            mkdir -p $(RULEDIR)/$$(echo $$(dirname $$file) | cut -d'/' -f3-);\
            cp $$file $(RULEDIR)/$$(echo $$(dirname $$file) | cut -d'/' -f3-);\
            mkdir -p $$(echo $$(dirname $$file) | cut -d'/' -f3-);\
            cp $$file $$(echo $$(dirname $$file) | cut -d'/' -f3-);\
        done
        echo "----------"
        pwd
        echo "-------------------------------------"
        echo $(RULEDIR)
        ls -l
        ./$(location @collectd_mbient//:build_sh)
        ls -l > $@
    """
    #&& ./configure --host x86_64-ubuntu-linux-gnu --disable-all-plugins \
    #--enable-buddyinfo \
    #--enable-cgroups \
    #--enable-contextswitch \
    #--enable-cpu \
    #--enable-df \
    #--enable-disk \
    #--enable-entropy \
    #--enable-ethstat \
    #--enable-interface \
    #--enable-irq \
    #--enable-load \
    #--enable-logfile \
    #--enable-match_empty_counter \
    #--enable-match_regex \
    #--enable-match_value \
    #--enable-memory \
    #--enable-processes \
    #--enable-rrdtool \
    #--enable-unixsock \
    #--enable-vmem \
    #--enable-write_graphite  \
    #--enable-write_log \
    #--enable-gps \
    #--enable-csv \
    #&& pwd \
    #&& echo $(RULEDIR) && echo $(OUTS) \
    #&& ls -l"# \
    #&& make all"
)
