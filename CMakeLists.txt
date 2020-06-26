# License: MIT. See LICENSE in root directory.
# Date: 2020/06/26

cmake_minimum_required(VERSION 3.1.0)

project("ensemble-drive-info" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

include_directories("${CMAKE_CURRENT_LIST_DIR}/inc")

set(ENSEMBLE_DRIVE_INFO_LIB "ensemble-drive-info-lib")
add_library(${ENSEMBLE_DRIVE_INFO_LIB} STATIC "")
target_sources(
    ${ENSEMBLE_DRIVE_INFO_LIB}
    PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}/src/ensemble/drive-info.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/inc/ensemble/drive-info.hpp"
)

if (CMAKE_BUILD_TYPE MATCHES "^[Dd]ebug")
    set(ENSEMBLE_DRIVE_INFO_EXE "ensemble-drive-info-exe")
    add_executable(${ENSEMBLE_DRIVE_INFO_EXE} "${CMAKE_CURRENT_LIST_DIR}/test/main.cpp")
    target_link_libraries(${ENSEMBLE_DRIVE_INFO_EXE} ${ENSEMBLE_DRIVE_INFO_LIB})
endif ()
