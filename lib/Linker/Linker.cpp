#include "Linker/Linker.h"
#include "utils/FileSystem.h"

namespace Linker {

Linker::Linker(const std::string &filename) {
  this->CurELF = std::make_unique<ELF::ELF>();
  this->CurParser = std::make_unique<Parser>(CurELF.get(), &fbuf);
  this->filename = filename;

  utils::FileSystem::readFile(this->filename, fbuf);
}

void Linker::Parse() { return this->CurParser->Parse(); }

} // namespace Linker
