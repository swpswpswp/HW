#pragma once

#include <cstdint>
#include <string>

class DoubleMemoryView
{
public:
    DoubleMemoryView();
    ~DoubleMemoryView() {}

    void set(double value);
    void setNaN();

    double getValue() const;
    std::string toHex64() const;

private:
    union
    {
        double value_;
        std::uint64_t bits_;
    };
};
