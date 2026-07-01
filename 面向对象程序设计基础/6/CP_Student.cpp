#include <iostream>
using namespace std;
#include "CP_Student.h"

void gb_swapStudent(CP_Student& a, CP_Student& b) {
	CP_Student t = a;
	a = b;
	b = t;
}