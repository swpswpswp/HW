#include "DoubleMemoryView.h"

#include <iostream>
#include <windows.h>

using namespace std;

static void setupConsoleUtf8()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

static void printMemoryHex(const DoubleMemoryView& view)
{
    cout << "0x" << view.toHex64() << endl;
}

int main()
{
    setupConsoleUtf8();

    DoubleMemoryView view;
    double input = 0.0;

    cout << "请输入一个双精度浮点数: ";
    if (!(cin >> input))
    {
        cout << "输入无效。" << endl;
        return 1;
    }

    view.set(input);
    cout << endl << input << " 在内存中的十六进制表示:" << endl;
    printMemoryHex(view);

    view.setNaN();
    cout << endl << "NaN 在内存中的十六进制表示:" << endl;
    printMemoryHex(view);

    return 0;
}
