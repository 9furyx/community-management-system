cmake_minimum_required(VERSION 3.5)

project (res_sys)

set(SOURCES
    src/bus.c
    src/util.c
    src/member.c
    src/linked_list.c
    src/main.c
    src/init.c
    src/main_ui.c
    src/path.c
    src/room.c
    src/checkin.c
    src/quick_sort.c
    src/staff.c
)

add_executable(ecms ${SOURCES})

target_include_directories(ecms
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(ecms m)

set(CMAKE_C_FLAGS_DEBUG  "-O2 -Wall -ggdb")
set(CMAKE_C_FLAGS_RELEASE  "-O2 -Wall")