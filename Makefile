BUILD_DIR = build
BIN = ${BUILD_DIR}/ProjectName

export VCPKG_ROOT

DEBUG_FLAGS = -DCMAKE_BUILD_TYPE=Debug
RELEASE_FLAGS = -DCMAKE_BUILD_TYPE=Release
BUILD_PROGRAM_FLAG = -G "Ninja"
TOOLCHAIN_FLAG = -DCMAKE_TOOLCHAIN_FILE="${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"

# E.G
# Main%: debug
# 	./${BUILD_DIR}/Pointer$(subst Pointer,,$@)

run: debug
	./${BIN}

debug: ${BUILD_DIR}/
	cd build && \
	cmake .. ${BUILD_PROGRAM_FLAG} ${TOOLCHAIN_FLAG} ${DEBUG_FLAGS} && \
	cmake --build .

release: ${BUILD_DIR}/
	cd build && \
	cmake .. ${BUILD_PROGRAM_FLAG} ${TOOLCHAIN_FLAG} ${RELEASE_FLAGS} && \
	cmake --build .

${BUILD_DIR}/:
	mkdir ${BUILD_DIR}

.PHONY: %
