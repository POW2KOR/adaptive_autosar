set(TARGET_NAME mbition_use_case_1)

add_library(${TARGET_NAME}
    use_case_1.cc
)

target_include_directories(${TARGET_NAME} 
    PUBLIC 
    includes
)

find_package(ARA REQUIRED)

target_link_libraries(${TARGET_NAME}
    PUBLIC
    ${ARA_LIBRARIES}
    mbition-app-prototype-generated-sources
)

target_compile_definitions(${TARGET_NAME}
    PUBLIC
    MBITION_USE_CASE_1
)