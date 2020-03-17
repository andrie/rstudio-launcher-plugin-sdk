#!/usr/bin/env bash

#
# create-test-users.sh
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

set -e # exit on failed commands

# Create the RStudio Server User, if it does not already exist
grep rstudio-server < /etc/passwd >/dev/null
ADD_USER=$?
if [[ $ADD_USER -ne 0 ]]; then
  sudo adduser --system rstudio-server
fi

sudo groupadd "rlpstestgrpone" >/dev/null
sudo groupadd "rlpstestgrptwo" >/dev/null
sudo groupadd "rlpstestgrpthree" >/dev/null
sudo useradd -p "" -g "rlpstestgrpone" "rlpstestusrone" >/dev/null
sudo useradd -p "" -g "rlpstestgrpone" -G "rlpstestgrptwo,rlpstestgrpthree" "rlpstestusrtwo" >/dev/null
sudo useradd -p "" -g "rlpstestgrptwo" "rlpstestusrthree" >/dev/null
sudo useradd -p "" -g "rlpstestgrptwo" -G "rlpstestgrpthree" "rlpstestusrfour" >/dev/null
sudo useradd -p "" -g "rlpstestgrpone" -G "rlpstestgrpthree" "rlpstestusrfive" >/dev/null
