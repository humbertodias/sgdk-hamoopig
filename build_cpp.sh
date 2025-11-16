#!/bin/bash
# Custom build script for C++ support in SGDK projects
# This script compiles .cpp files with g++ and then links with SGDK

set -e

# Configuration
SGDK_VERSION="2.11"
DOCKER_IMAGE="registry.gitlab.com/doragasu/docker-sgdk:v${SGDK_VERSION}"
PLATFORM="linux/amd64"

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${GREEN}Building SGDK C++ project...${NC}"

# Step 1: Compile C++ source files
echo -e "${YELLOW}Step 1: Compiling C++ files with g++...${NC}"

# Create output directory
mkdir -p out/src

# Compile main.cpp with g++
docker run --rm --entrypoint=/bin/bash \
    --user $(id -u):$(id -g) \
    -v "${PWD}":/workdir -w /workdir \
    --platform ${PLATFORM} \
    ${DOCKER_IMAGE} \
    -c "m68k-elf-g++ -DSGDK_GCC -m68000 \
        -fno-exceptions -fno-rtti \
        -fdiagnostics-color=always \
        -Wall -Wextra \
        -Wno-shift-negative-value \
        -Wno-main \
        -Wno-unused-parameter \
        -Wno-write-strings \
        -fno-builtin \
        -ffunction-sections \
        -fdata-sections \
        -fms-extensions \
        -I. -Iinc -Isrc -Ires \
        -I/sgdk/inc -I/sgdk/res \
        -B/sgdk/bin \
        -O3 -fuse-linker-plugin \
        -fno-web -fno-gcse \
        -fomit-frame-pointer \
        -flto -flto=auto -ffat-lto-objects \
        -c src/main.cpp -o out/src/main.o"

if [ $? -eq 0 ]; then
    echo -e "${GREEN}C++ compilation successful!${NC}"
else
    echo -e "${RED}C++ compilation failed!${NC}"
    exit 1
fi

echo -e "${GREEN}Build completed successfully!${NC}"
echo -e "${YELLOW}Note: Full linking with SGDK requires resource compilation${NC}"
echo -e "${YELLOW}Run 'make compile' after resources are set up for complete ROM build${NC}"
