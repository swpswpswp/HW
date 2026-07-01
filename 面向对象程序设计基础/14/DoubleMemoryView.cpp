#include "DoubleMemoryView.h"

#include <iomanip>
#include <limits>
#include <sstream>

DoubleMemoryView::DoubleMemoryView()
{
    value_ = 0.0;
}

void DoubleMemoryView::set(double value)
{
    value_ = value;
}

void DoubleMemoryView::setNaN()
{
    value_ = std::numeric_limits<double>::quiet_NaN();
}

double DoubleMemoryView::getValue() const
{
    return value_;
}

std::string DoubleMemoryView::toHex64() const
{
    std::ostringstream oss;
    oss << std::hex << std::uppercase << std::setfill('0') << std::setw(16) << bits_;
    return oss.str();
}
