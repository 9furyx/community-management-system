cmake_minimum_required(VERSION 3.5)

project (res_sys)

set(SOURCES
    src/bus.c
    src/util.c
    src/clear_sh.c
    src/member.c
)

add_executable(bus_test ${SOURCES})

target_include_directories(bus_test
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/include
)
