#include "ArrayManager.h"

// Since ArrayManager is a template class, implementation is in the header file
// This file can contain non-template helper functions if needed

// Explicit template instantiation for common types
template class ArrayManager<int>;
template class ArrayManager<double>;
template class ArrayManager<float>;
template class ArrayManager<char>;