# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

project(test_plugins)

cmake_minimum_required(VERSION 3.16)
cmake_policy(SET CMP0056 NEW)

find_package(Qt5WaylandClient REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Core_EXECUTABLE_COMPILE_FLAGS}")

include_directories(${Qt5WaylandClient_PRIVATE_INCLUDE_DIRS})
add_executable(test_waylandclient_exe main.cpp)
target_link_libraries(test_waylandclient_exe Qt5::WaylandClient)
