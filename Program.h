#ifndef PROGRAM_H
#define PROGRAM_H

#include <string>
#include "Location.h"

class Program {
    std::vector<Location> locations;
    std::map<std::string, int> labels;

    public:
        Program();

        std::string toBinaryString();

        void addInstruction(Location i); //Deprecated.

        void addInstruction(int op1, int op2, int op3, int op4);

        void addLoadLiteral(int value, int op1);

        void addLoadAddress(std::string label, int op1);

        void addLabel(std::string label_name);

        void addLiteralValue(int value);

        void addLiteralString(std::string str);

};
#endif