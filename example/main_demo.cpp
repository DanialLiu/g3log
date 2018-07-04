/** ==========================================================================
* 2011 by KjellKod.cc. This is PUBLIC DOMAIN to use at your own risk and comes
* with no warranties. This code is yours to share, use and modify with no
* strings attached and no restrictions or obligations.
 *
 * For more information see g3log/LICENSE or refer refer to http://unlicense.org
* ============================================================================*/

#include <g3log/log.h>
#include <iomanip>
#include <thread>
#include <iostream>


namespace
{
#if (defined(WIN32) || defined(_WIN32) || defined(__WIN32__))
   const std::string path_to_log_file = "./";
#else
   const std::string path_to_log_file = "/tmp/";
#endif
}

namespace example_fatal
{
   void killWithContractIfNonEqual(int first, int second)
   {
      CHECK(first == second, "tag_check") << "Test to see if contract works: onetwothree: " << 123 << ". This should be at the end of the log, and will exit this example";
   }
} // example fatal


int main(int argc, char **argv)
{
   auto log = base::initLog(path_to_log_file, argv[0]);
   LOGI("tag") << "this is info";
   LOGV("tag") << "this is verbose";
   LOGD("tag") << "this is debug";
   LOGW("tag") << "this is warning";
   LOGE("tag") << "this is error";
   LOGDF("tag", "string format %2d", 1);
   LOGIF("tag", "string format %0.3f", 3.1419526);
}

