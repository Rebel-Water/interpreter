#include "chunk.hpp"
#include <iostream>
#include <iomanip>
#include "util.hpp"
std::ostream &operator<<(std::ostream &os, Opcode op)
{
    const char *name = [&]()
    {
        switch (op)
        {
#define X(name)        \
    case Opcode::name: \
        return #name;
            OPCODE_NAMES
#undef X
        default:
            throw std::logic_error("Unexpected opcode");
        }
    }();
    os << name;
    return os;
}

std::ostream &operator<<(std::ostream &os, const Chunk &chunk)
{
    os << " === Bytecode === \n";
    for (int offset = 0; offset < static_cast<int>(chunk.bytecode.size());)
        offset = Util::disassembleInstruction(chunk, offset);
    return os;
}
