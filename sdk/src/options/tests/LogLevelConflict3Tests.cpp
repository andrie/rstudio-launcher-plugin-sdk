/*
 * LogLevelConflict3Tests.cpp
 * 
 * Copyright (C) 2019-20 by RStudio, PBC
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include <TestMain.hpp>

#include <boost/thread.hpp>

#include <options/Options.hpp>
#include <system/FilePath.hpp>
#include <system/User.hpp>

namespace rstudio {
namespace launcher_plugins {
namespace options {

TEST_CASE("log level conflict (less detail, command line) options")
{
   SECTION("read options")
   {
      constexpr const char* argv[] = {
            "options-test",               // The first element should be the process name. Make it up.
            "--enable-debug-logging=1"
      };
      constexpr int argc = 2;

      Options& opts = Options::getInstance();
      Error error = opts.readOptions(argc, argv, system::FilePath("./conf-files/LogLevelConflict3.conf"));
      REQUIRE_FALSE(error);
   }

   SECTION("check values")
   {
      Options& opts = Options::getInstance();
      system::User serverUser;
      Error error = opts.getServerUser(serverUser);
      REQUIRE_FALSE(error);

      CHECK(opts.getJobExpiryHours() == system::TimeDuration::Hours(24));
      CHECK(opts.getHeartbeatIntervalSeconds() == system::TimeDuration::Seconds(5));
      CHECK(opts.getLogLevel() == logging::LogLevel::DEBUG);
      CHECK(opts.getRSandboxPath().getAbsolutePath() == "/usr/lib/rstudio-server/bin/rsandbox");
      CHECK(opts.getScratchPath().getAbsolutePath() == "/var/lib/rstudio-launcher/");
      CHECK(serverUser.getUsername() == "rstudio-server");
      CHECK(opts.getThreadPoolSize() == std::max<unsigned int>(4, boost::thread::hardware_concurrency()));
   }
}

} // namespace options
} // namespace launcher_plugins
} // namespace rstudio

