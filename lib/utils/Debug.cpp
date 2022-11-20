#include <iostream>
#include <string>

#include "utils/Debug.h"

namespace utils {
namespace Debug {

void _Assert(bool cond, const std::string_view &fmt, ...) {
  if (!cond) {
    std::cerr << ANSI_FMT("[Fetal] ", ANSI_FG_RED) << fmt << std::endl;
    exit(EXIT_FAILURE);
  }
}

} // namespace Debug
} // namespace utils
