#!/usr/bin/env bash

#
# run-tests
#
# Copyright (C) 2020 by RStudio, PBC
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

FAILURES=0

sudo cp ./test.sh /home/rlpstestusrthree/test.sh
sudo chown rlpstestusrthree:rlpstestgrptwo /home/rlpstestusrthree/test.sh

sudo cp ./test.sh /home/rlpstestusrtwo/test.sh
sudo chown rlpstestusrtwo:rlpstestgrpone /home/rlpstestusrtwo/test.sh

for test in ./*-tests;
do
  if [[ "${test}" =~ .*-process-tests ]]; then
    echo "Running sudo ${test}..."
    sudo "${test}"
  else
    echo "Running ${test}..."
    ${test}
  fi
  FAILURES=$((FAILURES + $?))
done

echo -n $FAILURES > failures.log

if [[ $FAILURES -ne 0 ]]; then
  exit 1
fi

exit 0
