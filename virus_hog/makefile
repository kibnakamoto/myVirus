CXX ?= g++
CXXFLAGS ?= -std=c++20
EXEC ?= hog_memory.cpp
BIN ?= hog

hog: ${EXEC}
	${CXX} ${CXXFLAGS} ${EXEC} -o ${BIN}

clean:
	rm -rf ${BIN}

