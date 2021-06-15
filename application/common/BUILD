package(default_visibility = ["//visibility:public"])

cc_library(
    name = "application_base",
    srcs = [
        "application_base.cpp",
        "error_domain.cpp",
    ],
    hdrs = [
        "application_base.h",
        "error_domain.h",
    ],
    copts = [
        "-std=c++14",
    ],
    linkstatic = 1,
    deps = [
        "//bsw:amsr_vector_fs_applicationbase",
        "//bsw:amsr_vector_fs_em_executionmanager",
        "//bsw:amsr_vector_fs_libvac",
        "//bsw:amsr_vector_fs_log_api",
    ],
)
