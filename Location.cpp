#include <memory>
#include <bitset>
#include <map>
#include "Location.h"

using namespace std;

Location::Location(string str) {
    ins = str;
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
    if (value != -1) {
        return std::bitset<16>(value).to_string();
    }
    return ins;
}