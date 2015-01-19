#include <vector>
#include <map>
#include <sstream>
#include "Program.h"
#include "Location.h"

using namespace std;

void verifyOperand(int op) {
    if (op < 0 || op > 15) {
        throw overflow_error("Bad operand");
    }
}

std::vector<unsigned char> intToBytes(int paramInt) {
     std::vector<unsigned char> arrayOfByte(4);
     for (int i = 0; i < 4; i++)
         arrayOfByte[3 - i] = (paramInt >> (i * 8));
     return arrayOfByte;
}

Program::Program() {

}

std::string Program::toBinaryString() {
    stringstream str;

    for (int i = 0; i < locations.size(); i++) {
        str << i << " " << locations[i].toBinaryString(labels) << "\n";
    }

    return str.str();
}

void Program::addInstruction(Location i) {
    locations.push_back(i);
}

void Program::addInstruction(int op1, int op2, int op3, int op4) {
    verifyOperand(op1);
    verifyOperand(op2);
    verifyOperand(op3);
    verifyOperand(op4);

    locations.push_back(Location ((op1*16*16*16) + (op2*16*16) + (op3*16) + (op4)));
}

void Program::addLoadLiteral(int value, int op1) {
    verifyOperand(op1);
    vector<unsigned char> bytes = intToBytes(value);

    addInstruction(I_LDU, op1, bytes[2] / 16, bytes[2] % 16);
    addInstruction(I_LDL, op1, bytes[3] / 16, bytes[3] % 16);
}

void Program::addLoadAddress(std::string label, int op1) {
    verifyOperand(op1);
    locations.push_back(Location((16 * I_LDU) + op1, label, true));
    locations.push_back(Location((16 * I_LDL) + op1, label, false));
}

void Program::addLabel(string label_name) {
    labels.emplace(label_name, locations.size());
}

void Program::addLiteralValue(int value) {
    locations.push_back(Location(value));
}

void Program::addLiteralString(std::string str) {

}



