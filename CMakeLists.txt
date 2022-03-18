cmake_minimum_required(VERSION 3.5)
project(
    "FlailSnail"
    VERSION 0.0.0 # TODO some way to grab this from `git describe`?
    DESCRIPTION "A library for  describing a C/C++/Fortran run in detail, using only a single function call"
    LANGUAGES C CXX Fortran
)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# Get lists of source files
file(GLOB_RECURSE C_SRC_FILES "${CMAKE_SOURCE_DIR}/src/*.c")

# Create library
add_library(${PROJECT_NAME} ${C_SRC_FILES})

# Configure library options
# - tell cmake where to find header files for either building or installing
target_include_directories(
    ${PROJECT_NAME} 
    PRIVATE 
    $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# Compile with better warnings
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)

# Set install instructions
install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}_Targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Set versioning info
write_basic_package_version_file("${PROJECT_NAME}ConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMinorVersion
)

configure_package_config_file(
    "${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in"
    "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION
    ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake
)

# Set targets to install
install(EXPORT ${PROJECT_NAME}_Targets
        FILE ${PROJECT_NAME}Targets.cmake
        NAMESPACE ${PROJECT_NAME}::
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake
)

# install Cmake bits
install(
    FILES 
        "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION 
        ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake
)

# install project-level headers to system include dir
install(
    FILES 
        ${PROJECT_SOURCE_DIR}/${PROJECT_NAME}.h 
        ${PROJECT_SOURCE_DIR}/${PROJECT_NAME}.hpp
    DESTINATION 
        ${CMAKE_INSTALL_INCLUDEDIR}
)
# install project include dir to system include dir
install(
    DIRECTORY 
        ${PROJECT_SOURCE_DIR}/include 
    DESTINATION
        ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
)
