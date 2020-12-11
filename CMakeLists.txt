cmake_minimum_required(VERSION 3.5)

project (res_sys)

set(SOURCES
    src/bus.c
    src/util.c
    src/member.c
    src/linked_list_template.c
    src/main.c
    src/init.c
    src/main_ui.c
    src/path.c
    src/room.c
)

add_executable(test ${SOURCES})

target_include_directories(test
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/include
)

set(CMAKE_BUILD_TYPE Debug)