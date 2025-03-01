CC = g++
BUILD_DIR = build
LIBS_DIR = libs
SRC_DIR = src
TESTS_DIR = tests
INC_DIR = include
C_FLAGS = -fopenmp -g -std=gnu++11
SHARED_OBJECT_NAME = moar_zeta_cpp_openmp

ALGLIB_OBJS = ${BUILD_DIR}/${LIBS_DIR}/alglib/alglibinternal.o ${BUILD_DIR}/${LIBS_DIR}/alglib/alglibmisc.o ${BUILD_DIR}/${LIBS_DIR}/alglib/ap.o
TEST_FW_FILES = ${LIBS_DIR}/array_matcher/matcher.hpp ${LIBS_DIR}/catch2/catch.hpp

ALL_SRC_OBJS = ${BUILD_DIR}/${SRC_DIR}/local_zeta.o ${BUILD_DIR}/${SRC_DIR}/single_testing.o ${BUILD_DIR}/${SRC_DIR}/moar_zeta.o
BINDINGS = ${BUILD_DIR}\${SRC_DIR}\bindings.o

### how to build directory structure

${BUILD_DIR}:
	mkdir ${BUILD_DIR}

${BUILD_DIR}/${LIBS_DIR}: ${BUILD_DIR}
	mkdir ${BUILD_DIR}/${LIBS_DIR}

${BUILD_DIR}/${SRC_DIR}: ${BUILD_DIR}
	mkdir ${BUILD_DIR}/${SRC_DIR}

${BUILD_DIR}/${TESTS_DIR}: ${BUILD_DIR}
	mkdir ${BUILD_DIR}/${TESTS_DIR}

${BUILD_DIR}/${LIBS_DIR}/alglib: ${BUILD_DIR}/${LIBS_DIR}
	mkdir ${BUILD_DIR}/${LIBS_DIR}/alglib

${BUILD_DIR}/${LIBS_DIR}/array_matcher: ${BUILD_DIR}/${LIBS_DIR}
	mkdir ${BUILD_DIR}/${LIBS_DIR}/array_matcher

${BUILD_DIR}/${LIBS_DIR}/catch2: ${BUILD_DIR}/${LIBS_DIR}
	mkdir ${BUILD_DIR}/${LIBS_DIR}/catch2


### how to compile libraries

${BUILD_DIR}/${LIBS_DIR}/alglib/%.o: ${LIBS_DIR}/alglib%.cpp | ${BUILD_DIR}/${LIBS_DIR}/alglib
	${CC} -c $< -I${LIBS_DIR}/alglib -o $@

${BUILD_DIR}/${LIBS_DIR}/array_matcher/matcher.o: ${LIBS_DIR}/array_matcher/matcher.hpp | ${BUILD_DIR}/${LIBS_DIR}/array_matcher
	${CC} -c $< -I${LIBS_DIR}/alglib -o $@

${BUILD_DIR}/${LIBS_DIR}/catch2/catch.o: ${LIBS_DIR}/catch2/catch.hpp | ${BUILD_DIR}/${LIBS_DIR}/catch2
	${CC} -c $< -I${LIBS_DIR}/alglib -o $@


### how to compile tests

${BUILD_DIR}/${SRC_DIR}/moar_zeta.o: ${SRC_DIR}/moar_zeta.cpp ${INC_DIR}/moar_zeta/moar_zeta.h | ${BUILD_DIR}/${SRC_DIR}
	${CC} ${C_FLAGS} -c -I${INC_DIR} -o $@ $<

${BUILD_DIR}/${SRC_DIR}/bindings.o: ${SRC_DIR}/bindings.cpp ${INC_DIR}/moar_zeta/bindings.h | ${BUILD_DIR}/${SRC_DIR}
	${CC} ${C_FLAGS} -c -I${INC_DIR} -o $@ $<

${BUILD_DIR}/${SRC_DIR}/%.o: ${SRC_DIR}%.cpp ${SRC_DIR}%.h | ${BUILD_DIR}/${SRC_DIR}
	${CC} ${C_FLAGS} -c -I${LIBS_DIR}/alglib -o $@ $<

${BUILD_DIR}/${TESTS_DIR}/%.o: ${TESTS_DIR}%.cpp | ${BUILD_DIR}/${TESTS_DIR}
	${CC} ${C_FLAGS} -I${INC_DIR} -I${LIBS_DIR}/catch2 -I${LIBS_DIR}/array_matcher -I${SRC_DIR} -c -o $@ $<


${BUILD_DIR}/${TESTS_DIR}/test_local_zeta: ${BUILD_DIR}/${TESTS_DIR}/test_local_zeta.o ${BUILD_DIR}/${SRC_DIR}/local_zeta.o | ${ALGLIB_OBJS} ${TEST_FW_OBJS}
	${CC} ${C_FLAGS} -o $@ ${BUILD_DIR}/${TESTS_DIR}/test_local_zeta.o ${BUILD_DIR}/${SRC_DIR}/local_zeta.o ${ALGLIB_OBJS} ${TEST_FW_FILES}

${BUILD_DIR}/${TESTS_DIR}/test_single_testing: ${BUILD_DIR}/${TESTS_DIR}/test_single_testing.o ${BUILD_DIR}/${SRC_DIR}/single_testing.o | ${ALGLIB_OBJS} ${TEST_FW_OBJS}
	${CC} ${C_FLAGS} -o $@ ${BUILD_DIR}/${TESTS_DIR}/test_single_testing.o ${BUILD_DIR}/${SRC_DIR}/single_testing.o ${TEST_FW_FILES}

${BUILD_DIR}/${TESTS_DIR}/test_moar_zeta: ${BUILD_DIR}/${TESTS_DIR}/test_moar_zeta.o | ${ALGLIB_OBJS} ${TEST_FW_OBJS} ${ALL_SRC_OBJS}
	${CC} ${C_FLAGS} -o $@ ${BUILD_DIR}/${TESTS_DIR}/test_moar_zeta.o ${ALL_SRC_OBJS} ${ALGLIB_OBJS} ${TEST_FW_FILES}

tests: ${BUILD_DIR}/${TESTS_DIR}/test_local_zeta ${BUILD_DIR}/${TESTS_DIR}/test_single_testing ${BUILD_DIR}/${TESTS_DIR}/test_moar_zeta

shared_object: ${ALGLIB_OBJS} ${TEST_FW_OBJS} ${ALL_SRC_OBJS} ${BINDINGS}
	${CC} ${C_FLAGS} -O3 -shared -o ${BUILD_DIR}/${SHARED_OBJECT_NAME} ${BINDINGS} ${ALL_SRC_OBJS} ${ALGLIB_OBJS}

clean:
	rm -rf ${BUILD_DIR}

.PHONY: tests shared_object clean