#include "Util.h"

using namespace std;

char getEscapedChar(char c) {
    switch (c) {
        case '0':
            return '\0';
        case '\'':
            return '\'';
        case '\"':
            return '\"';
        case '?':
            return '?';
        case '\\':
            return '\\';
        case 'a':
            return '\a';
        case 'b':
            return '\b';
        case 'f':
            return '\f';
        case 'n':
            return '\n';
        case 'r':
            return '\r';
        case 't':
            return '\t';
        case 'v':
            return '\v';
        default:
            return c;
    }
}

std::vector<unsigned char> intToBytes(int paramInt) {
     std::vector<unsigned char> arrayOfByte(4);
     for (int i = 0; i < 4; i++)
         arrayOfByte[3 - i] = (paramInt >> (i * 8));
     return arrayOfByte;
}

void verifyOperand(int op) {
    if (op < 0 || op > 15) {
        throw overflow_error("Bad operand");
    }
}
