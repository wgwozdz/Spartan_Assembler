#include <vector>
#include <map>
#include <sstream>
#include <stdio.h>
#include "Program.h"
#include "Location.h"

using namespace std;

void verifyOperand(int op) {
    if (op < 0 || op > 15) {
        throw overflow_error("Bad operand");
    }
}

vector<unsigned char> intToBytes(int paramInt)
{
     vector<unsigned char> arrayOfByte(4);
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

    printf("Got literal %d %d %d %d", bytes[3], bytes[2], bytes[1], bytes[0]);

    addInstruction(I_LDU, op1, bytes[2] / 16, bytes[2] % 16);
    addInstruction(I_LDL, op1, bytes[3] / 16, bytes[3] % 16);
}

void Program::addLabel(string label_name) {
    labels.emplace(label_name, locations.size());
}

void Program::addLiteralValue(int value) {
    locations.push_back(Location(value));
}

void Program::addLiteralString(std::string str) {

}



