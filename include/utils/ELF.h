#ifndef ELF_H
#define ELF_H

#include <algorithm>
#include <cassert>
#include <string>
#include <vector>

#include <elf.h>

namespace ELF {

class ELF {
public:
  ~ELF() = default;
  ELF() = default;

public:
  void setEhdr(Elf64_Ehdr &e) { this->ehdr = e; }
  Elf64_Ehdr &getEhdr() { return this->ehdr; };

  void setShdr(Elf64_Shdr &shdr, std::string &str) {
    ShdrTab.push_back(shdr);
    StrTab.push_back(str);
    assert(ShdrTab.size() == StrTab.size());
  }

  Elf64_Shdr *getShdr(std::size_t idx) { return &ShdrTab[idx]; }

  Elf64_Shdr *findSection(const uint32_t t) {
    auto find =
        std::find_if(ShdrTab.begin(), ShdrTab.end(),
                     [&](Elf64_Shdr e) -> bool { return e.sh_type == t; });
    return (find != ShdrTab.end()) ? &*find : nullptr;
  }

  void setSymTab(Elf64_Sym &S, std::string &N) {
    SymTab.push_back(S);
    SymStrTab.push_back(N);
    assert(SymTab.size() == SymStrTab.size());
  }

private:
  // ELF header
  Elf64_Ehdr ehdr;
  // section header
  std::vector<Elf64_Shdr> ShdrTab;
  // String table
  std::vector<std::string> StrTab;
  // Symbol table
  std::vector<Elf64_Sym> SymTab;
  // Symbol string table
  std::vector<std::string> SymStrTab;
};

} // namespace ELF

#endif // ELF_H
