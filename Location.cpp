#include <memory>
#include <bitset>
#include <vector>
#include <map>
#include "Location.h"
#include "Util.h"

using namespace std;

Location::Location() {
    value = -1;
}

Location::Location(int val) {
    if (val < 0) {
        throw underflow_error ("I dont support negatives");
    }
    if (val > 65535) {
        throw overflow_error ("Value is larger than a location");
    }
    value = val;
}

string Location::toBinaryString(std::map<std::string, int> labels) {
    return std::bitset<16>(value).to_string();
}

UpperLoadAddr::UpperLoadAddr(std::string label, int op1, int op2) {
    this->op1 = op1;
    this->op2 = op2;
    this->label = label;
}

string UpperLoadAddr::toBinaryString(std::map<std::string, int> labels) {
    vector<unsigned char> bytes = intToBytes(labels[label]);
    return std::bitset<16>((op1 << 12) + (op2 << 8) + (bytes[2])).to_string();
}

LowerLoadAddr::LowerLoadAddr(std::string label, int op1, int op2) : UpperLoadAddr(label, op1, op2) { }

string LowerLoadAddr::toBinaryString(std::map<std::string, int> labels) {
    vector<unsigned char> bytes = intToBytes(labels[label]);
    return std::bitset<16>((op1 << 12) + (op2 << 8) + (bytes[3])).to_string();
}

LiteralLabel::LiteralLabel(std::string label) {
    this->label = label;
}

string LiteralLabel::toBinaryString(std::map<std::string, int> labels) {
    int value = labels.count(label) > 0 ? labels[label] : 0;
    return std::bitset<16>(value).to_string();
}
