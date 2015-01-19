#include <memory>
#include <bitset>
#include <vector>
#include <map>
#include "Location.h"

using namespace std;

Location::Location(string str) {
    ins = str;
    value = -1;
    isUpper = false;
    isLabelLoad = false;
}

std::vector<unsigned char> intToByteV(int paramInt) {
     std::vector<unsigned char> arrayOfByte(4);
     for (int i = 0; i < 4; i++)
         arrayOfByte[3 - i] = (paramInt >> (i * 8));
     return arrayOfByte;
}

Location::Location(int val) {
    if (val < 0) {
        throw underflow_error ("I dont support negatives");
    }
    if (val > 65535) {
        throw overflow_error ("Value is larger than a location");
    }
    value = val;
    isUpper = false;
    isLabelLoad = false;
}

Location::Location(int upperHalf, std::string label, bool upper) {
    value = upperHalf;
    labelName = label;
    isUpper = upper;
    isLabelLoad = true;
}

string Location::toBinaryString(std::map<std::string, int> labels) {
    if (isLabelLoad) {
        vector<unsigned char> bytes = intToByteV(labels[labelName]);
        if (isUpper) {
            return std::bitset<16>((value << 8) + bytes[2]).to_string();
        }
        return std::bitset<16>((value << 8) + bytes[3]).to_string();
    }
    if (value != -1) {
        return std::bitset<16>(value).to_string();
    }
    return ins;
}