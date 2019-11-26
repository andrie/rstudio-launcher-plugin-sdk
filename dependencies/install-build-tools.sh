#!/usr/bin/env bash

#
# install-build-tools
#
# Copyright (C) 2019 by RStudio, Inc.
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#

HAVE_YUM=1
yum 2>/dev/null
if [[ $? -eq 127 ]]; then
    HAVE_YUM=0
fi

CMAKE_VER=($(cmake --version | cut -d ' ' -f 3))
CMAKE_VER=${CMAKE_VER[0]}
CMAKE_MAJOR_VER=${CMAKE_VER%%.*}
CMAKE_MINOR_VER=${CMAKE_VER%.*}
CMAKE_MINOR_VER=${CMAKE_MINOR_VER#*.}

set -e

CPU_COUNT=0
CPU_CORES_ARR=($(cat /proc/cpuinfo | grep "cores" | cut -d ':' -f 2 | tr -d ' '))
for I in $CPU_CORES_ARR; do
    CPU_COUNT=$(expr $CPU_COUNT + $I)
done

if [[ ( -z $CMAKE_VER ) || ( $CMAKE_MAJOR_VER -lt 3 ) || ( ( $CMAKE_MAJOR_VER -eq 3 ) && ( $CMAKE_MINOR_VER -lt 14 ) ) ]]; then

    if [[ $HAVE_YUM -eq 1 ]]; then
        sudo yum update -y
        sudo yum install -y wget gcc g++ make
    else
        sudo apt update
        sudo apt install -y wget gcc g++ make
    fi

    CMAKE_VER="3.15.5"
    CMAKE_TAR="cmake-${CMAKE_VER}.tar.gz"

    mkdir temp
    cd temp
    wget "https://cmake.org/files/v${CMAKE_VER}}/${CMAKE_TAR}"
    tar -xzf "${CMAKE_TAR}"
    cd "${CMAKE_TAR%.tar.gz}"

    ./bootstrap
    make -j $(expr $CPU_COUNT / 2)
    sudo make install

else
    echo "CMake version ${CMAKE_VER} is already installed."
fi