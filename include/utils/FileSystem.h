#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <string>
#include <vector>

namespace utils{
namespace FileSystem {

void readFile(const std::string &filename, std::vector<char> &buffer);


} // namespace FileSystem
} // namespace utils

#endif // FILESYSTEM_H
