#include "CP_StudentSystem.h"
#include <cstdio>
#ifdef _WIN32
#include <windows.h>
#endif

int main(int argc, char* argv[]) {
#ifdef _WIN32
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
#endif
	if (argc > 1) {
		FILE* fp = nullptr;
		if (freopen_s(&fp, argv[1], "r", stdin) != 0 || fp == nullptr) {
			return 1;
		}
	}
	CP_StudentSystem sys;
	sys.mb_run();
	return 0;
}
