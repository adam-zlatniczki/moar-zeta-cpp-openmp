CC = g++
BUILD_DIR = build
LIBS_DIR = libs
SRC_DIR = src
TESTS_DIR = tests

ifeq ($(OS),Windows_NT)
	RM = del /Q
	EXT = dll
else
	RM = rm -f
	EXT = so
endif

alglib: 
	echo "Compiling alglib"
	${CC} -c ${LIBS_DIR}/alglib/alglibinternal.cpp -I${LIBS_DIR}/alglib -o ${BUILD_DIR}/alglibinternal.o
	${CC} -c ${LIBS_DIR}/alglib/alglibmisc.cpp -I${LIBS_DIR}/alglib -o ${BUILD_DIR}/alglibmisc.o
	${CC} -c ${LIBS_DIR}/alglib/ap.cpp -I${LIBS_DIR}/alglib -o ${BUILD_DIR}/ap.o

array_matcher: ${LIBS_DIR}/array_matcher/matcher.hpp
	echo "Compiling array_matcher"
	${CC} -c ${LIBS_DIR}/array_matcher/matcher.hpp -o ${BUILD_DIR}/matcher.o

catch2:
	echo "Compiling catch2"
	${CC} -c ${LIBS_DIR}/catch2/catch.hpp -o ${BUILD_DIR}/catch.o

libs: alglib array_matcher catch2
	echo "Compiling libraries"

test_local_zeta: libs ${TESTS_DIR}/test_local_zeta.cpp
	${CC} -o ${BUILD_DIR}/test_local_zeta -I${LIBS_DIR}/** -I${SRC_DIR} ${BUILD_DIR}/alglibinternal.o ${BUILD_DIR}/alglibmisc.o ${BUILD_DIR}/ap.o ${BUILD_DIR}/matcher.o ${BUILD_DIR}/catch.o ${TESTS_DIR}/test_local_zeta.cpp

clean:
	${RM} ${BUILD_DIR}