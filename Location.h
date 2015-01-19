#ifndef LOCATION_H
#define LOCATION_H

#include <string>
#include <vector>

class Location {
    std::string ins;
    int value;
    bool isLabelLoad;
    bool isUpper;
    std::string labelName;

    public:
        Location(std::string str); // Deprecated.

        Location(int val);

        Location(int upperHalf, std::string label, bool upper); // Should be a subclass.

        std::string toBinaryString(std::map<std::string, int> labels);
};

enum FirstOp {
    I_ADD =  1,
    I_SUB =  2,
    I_MUL =  3,
    I_DIV =  4,
    I_MOD =  5,
    I_AND =  6,
    I_OR  =  7,
    I_XOR =  8,
    I_SHR =  9,
    I_SHL = 10,
    I_LDU = 11,
    I_LDL = 12,
    I_MORE= 15
};

enum SecondOp {
    I_MOV =  1,
    I_CMP =  2,
    I_JMP =  3,
    I_LDM =  4,
    I_STM =  5,
    I_NEG =  6,

    I_IOI =  8,
    I_IOO =  9,
    I_STI = 10,
    I_DLD = 11,
    I_CAL = 12,
};

enum ThirdOp {
    I_GTF =  1,
    I_STF =  2,
    I_INC =  3,
    I_DEC =  4,
};

enum FourthOp {
    I_RIT =  1,
    I_NOP = 15
};

enum Jump {
    J_EQ  = 1,
    J_LT  = 2,
    J_GT  = 4,
    J_NE  = 6,
    J_GE  = 5,
    J_LE  = 3,
    J_A   = 7

};

    template<typename ... Args>
    std::string string_format(const std::string& format, Args ... args){
        size_t size = 1 + snprintf(nullptr, 0, format.c_str(), args ...);
        std::unique_ptr<char[]> buf(new char[size]);
        snprintf(buf.get(), size, format.c_str(), args ...);
        return std::string(buf.get(), buf.get() + size);
    }

#endif