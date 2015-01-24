#include <vector>
#include <map>
#include <sstream>
#include <string>
#include "Program.h"
#include "Location.h"
#include "util.h"

using namespace std;

Program::Program() {

}

void Program::start() {
    char handler_label[100];
    for (int i = 0; i < 16; i++) {
        sprintf(handler_label, "interrupthandler%02d", i);
        locations.push_back(new LiteralLabel(string(handler_label)));
    }
    addLoadAddress("main", 0);
    addInstruction(I_MORE, I_JMP, J_A, 0);
    locations.push_back(new Location(0));
}

void Program::finish() {
    locations.push_back(new Location(0));
    addLabel("_stackstart");
}

std::string Program::toBinaryString() {
    stringstream str;

    for (int i = 0; i < locations.size(); i++) {
        str << "assign mem[" << i << "] = 16'b" << locations[i]->toBinaryString(labels) << ";\n";
    }

    return str.str();
}

void Program::addInstruction(int op1, int op2, int op3, int op4) {
    verifyOperand(op1);
    verifyOperand(op2);
    verifyOperand(op3);
    verifyOperand(op4);

    locations.push_back(new Location((op1*16*16*16) + (op2*16*16) + (op3*16) + (op4)));
}

void Program::addLoadLiteral(int value, int op1) {
    verifyOperand(op1);
    vector<unsigned char> bytes = intToBytes(value);

    addInstruction(I_LDU, op1, bytes[2] / 16, bytes[2] % 16);
    addInstruction(I_LDL, op1, bytes[3] / 16, bytes[3] % 16);
}

void Program::addLoadAddress(std::string label, int op1) {
    verifyOperand(op1);
    locations.push_back(new UpperLoadAddr(label, I_LDU, op1));
    locations.push_back(new LowerLoadAddr(label, I_LDU, op1));
}

void Program::addLabel(string label_name) {
    labels.emplace(label_name, locations.size());
}

void Program::addLiteralValue(int value) {
    locations.push_back(new Location(value));
}

void Program::addLiteralString(std::string str) {
    bool escaped = false;
    for (int i = 1; i < str.length() - 1; i++) {
        char c = str[i];
        if (!escaped && c == '\\') {
            escaped = true;
        } else if (escaped) {
            escaped = false;
            locations.push_back(new Location(getEscapedChar(c)));
        } else {
            escaped = false;
            locations.push_back(new Location(c));
        }
    }
    locations.push_back(new Location('\0'));
}



