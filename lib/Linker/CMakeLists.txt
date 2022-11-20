add_library(Linker
    Linker.cpp
    Parser.cpp
)

target_link_libraries(Linker
  utils
)
