cmake_minimum_required(VERSION 3.5)

project(bfl LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(bfl main.cpp
    interpretator.h interpretator.cpp
    args.h args.cpp
    README.md)

include(GNUInstallDirs)
install(TARGETS bfl
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
