# vi: set ft=cmake:

#
# CMakeLists.txt
#
# Copyright (C) 2019-20 by RStudio, PBC
#
# Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
# documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
# rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
# permit persons to whom the Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
# Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
# WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
# COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
# OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#

set(RLPS_COMMS_TEST_MAIN ../../tests/TestMain.cpp)

# Copy the test runner that runs all options tests.
configure_file(../../tests/run-tests.sh run-tests.sh COPYONLY)

# Allow files in the tests folder to be included
include_directories(
   ../../tests
)

# Abstract Communicator Tests
add_executable(rlps-abstract-communicator-tests
   ${RLPS_COMMS_TEST_MAIN}
   AbstractCommunicatorTests.cpp
   ${RLPS_HEADER_FILES}
   )

target_link_libraries(rlps-abstract-communicator-tests
   rstudio-launcher-plugin-sdk-lib
   ${RLPS_BOOST_LIBS}
   )


# Message Handler Tests
add_executable(rlps-message-handler-tests
   ${RLPS_COMMS_TEST_MAIN}
   MessageHandlerTests.cpp
   ${RLPS_HEADER_FILES}
)

target_link_libraries(rlps-message-handler-tests
   rstudio-launcher-plugin-sdk-lib
   ${RLPS_BOOST_LIBS}
)
