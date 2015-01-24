#ifndef LOCATION_H
#define LOCATION_H

#include <string>
#include <vector>

class Location {
    protected:
        int value;
        Location();

    public:
        Location(int val);
        virtual std::string toBinaryString(std::map<std::string, int> labels);
};

class UpperLoadAddr : public Location {
    protected:
        std::string label;
        int op1;
        int op2;

    public:
        UpperLoadAddr(std::string label, int op1, int op2);
        virtual std::string toBinaryString(std::map<std::string, int> labels) override;
};

class LowerLoadAddr : public UpperLoadAddr {
    public:
        LowerLoadAddr(std::string label, int op1, int op2);
        virtual std::string toBinaryString(std::map<std::string, int> labels) override;
};

class LiteralLabel : public Location {
    protected:
        std::string label;

    public:
        LiteralLabel(std::string label);
        virtual std::string toBinaryString(std::map<std::string, int> labels) override;
};

#endif