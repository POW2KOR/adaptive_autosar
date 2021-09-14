cmake_minimum_required(VERSION 3.16)
project(AdaptiveAutosar)

add_custom_command(
    # Fetch Adaptive Autosar binaries
    OUTPUT "aa_binaries_build"
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/build.sh ${BUILD_TARGET}
    installfct
    COMMENT "Executing bazel build of Adaptive Autosar for ${BUILD_TARGET}."

    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    VERBATIM
)

add_custom_target(build ALL DEPENDS "aa_binaries_build" VERBATIM)

# Install files
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/out/civic/${BUILD_TARGET}/etc/ DESTINATION ${CMAKE_INSTALL_PREFIX}/etc)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/out/civic/${BUILD_TARGET}/opt/ DESTINATION ${CMAKE_INSTALL_PREFIX}/opt)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/out/civic/${BUILD_TARGET}/sbin/ DESTINATION ${CMAKE_INSTALL_PREFIX}/sbin)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/out/civic/${BUILD_TARGET}/usr/ DESTINATION ${CMAKE_INSTALL_PREFIX}/usr)
