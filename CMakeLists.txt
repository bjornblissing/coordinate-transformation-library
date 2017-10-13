cmake_minimum_required(VERSION 3.5)

project(coordinate-transformation-library VERSION 1.0)

# Enable CTest
enable_testing()

set(LIBRARY_NAME coordinate-transformation)

# Target source files
set(LIBRARY_SOURCES
  src/gausskreuger.cpp
  src/position.cpp
  src/rt90position.cpp
  src/sweref99position.cpp
  src/wgs84position.cpp
)

# Target headerfiles
SET(LIBRARY_HEADERS
  include/gausskreuger.h
  include/position.h
  include/rt90position.h
  include/sweref99position.h
  include/wgs84position.h
)

###############################################################################
# Compiler Options
################################################################################

list(APPEND MSVC_OPTIONS /W4) # Warning level 4
list(APPEND MSVC_OPTIONS /WX) # Warnings as errors

list(APPEND GCC_OPTIONS -Wall)     # All warnings
list(APPEND GCC_OPTIONS -ansi)     # All warnings
list(APPEND GCC_OPTIONS -pedantic) # All warnings
list(APPEND GCC_OPTIONS -Wextra)   # Add extra warings

list(APPEND CLANG_OPTIONS -Wall)     # All warnings
list(APPEND CLANG_OPTIONS -Wextra)   # Add extra warings

add_library(${LIBRARY_NAME} ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})

target_compile_options(${LIBRARY_NAME} PRIVATE 
  $<$<CXX_COMPILER_ID:MSVC>:${MSVC_OPTIONS}>
  $<$<CXX_COMPILER_ID:GNU>:${GCC_OPTIONS}>
  $<$<CXX_COMPILER_ID:Clang>:${CLANG_OPTIONS}>
)

target_compile_features(${LIBRARY_NAME} PUBLIC cxx_auto_type cxx_strong_enums)

target_include_directories(${LIBRARY_NAME} PUBLIC 
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>
  $<INSTALL_INTERFACE:include> 
)


#####################################################################
# Export library
#####################################################################

set(LIBRARY_EXPORT_NAME coordinate-transformation-targets)


set_target_properties(${LIBRARY_NAME} PROPERTIES PUBLIC_HEADER "${LIBRARY_HEADERS}")

install(TARGETS ${LIBRARY_NAME} EXPORT ${LIBRARY_EXPORT_NAME}
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  PUBLIC_HEADER DESTINATION include
)

install(EXPORT ${LIBRARY_EXPORT_NAME}
  FILE ${LIBRARY_EXPORT_NAME}.cmake
  NAMESPACE VTI::
  DESTINATION lib/cmake/${LIBRARY_NAME}
)


#####################################################################
# Define tests
#####################################################################

set(TEST_NAME tests)
add_executable(${TEST_NAME} tests/tests.cpp)
target_link_libraries(${TEST_NAME} PRIVATE ${LIBRARY_NAME})

add_test(RT90toWGS84 ${TEST_NAME} 1)
add_test(WGS84ToRT90 ${TEST_NAME} 2)
add_test(WGS84ToSweref ${TEST_NAME} 3)
add_test(SwerefToWGS84 ${TEST_NAME} 4)
add_test(WGS84Parse ${TEST_NAME} 5)
