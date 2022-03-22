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
set(${PROJECT_NAME}_C_SOURCES
    ./include/FlailSnail/FlailSnail.h
    ./include/FlailSnail/compilers.h
    ./include/FlailSnail/print_provenance_log.h
    ./include/FlailSnail/utils.h
    ./src/print_provenance_log.c
    ./src/utils.c
)

# Create library
add_library(${PROJECT_NAME} ${${PROJECT_NAME}_C_SOURCES})
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

# Configure library options
# - tell cmake where to find header files for either building or installing
target_include_directories(
    ${PROJECT_NAME} 
    PUBLIC
    $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# Compile with better warnings
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)


########################
# Tests

string(COMPARE EQUAL "${PROJECT_NAME}" "${CMAKE_PROJECT_NAME}" PROJECT_IS_TOP_LEVEL)
if(PROJECT_IS_TOP_LEVEL)
    enable_testing()

    # Targets for building tests
    add_custom_target(build-tests)
    add_subdirectory(tests EXCLUDE_FROM_ALL)
    
    # Targets for running tests
    add_custom_target(run-tests
        COMMAND ctest --output-on-failure
    )
    add_dependencies(run-tests build-tests)
endif()

########################
# Install

# Set install instructions
install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}Targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Set versioning info
write_basic_package_version_file("${PROJECT_NAME}ConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    "${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in"
    "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION
    ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake
)

# Set targets to install
install(
    EXPORT ${PROJECT_NAME}Targets
    FILE ${PROJECT_NAME}Targets.cmake
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

# install Cmake bits
install(
    FILES 
        "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION 
        ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake
)

# install project include dir to system include dir
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
