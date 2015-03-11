# Target name
SET(TARGET_LIBRARYNAME coordinate-transformation)

# Target source files
SET(TARGET_LIB_SRC
	gausskreuger.cpp
	position.cpp
	rt90position.cpp
	sweref99position.cpp
	wgs84position.cpp
)

# Target headerfiles
SET(TARGET_LIB_H
	gausskreuger.h
	position.h
	rt90position.h
	sweref99position.h
	wgs84position.h
)

#####################################################################
# Create library
#####################################################################

ADD_LIBRARY(${TARGET_LIBRARYNAME} ${TARGET_LIB_SRC} ${TARGET_LIB_H})

#####################################################################
# Create test executable
#####################################################################
SET(TESTS_TARGETNAME Tests)
ADD_EXECUTABLE(${TESTS_TARGETNAME} tests.cpp)
TARGET_LINK_LIBRARIES(${TESTS_TARGETNAME} ${TARGET_LIBRARYNAME})

SET(TEST_BINARY ${PROJECT_BINARY_DIR}/bin/${TESTS_TARGETNAME})

ADD_TEST (RT90toWGS84 ${TEST_BINARY} 1)
ADD_TEST (WGS84ToRT90 ${TEST_BINARY} 2)
ADD_TEST (WGS84ToSweref ${TEST_BINARY} 3)
ADD_TEST (SwerefToWGS84 ${TEST_BINARY} 4)
ADD_TEST (WGS84Parse ${TEST_BINARY} 5)
