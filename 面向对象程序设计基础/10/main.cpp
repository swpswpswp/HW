#include "ArrayManager.h"
#include <iostream>
#include <string>

// Helper function: print array contents
template<typename T>
void printArray(const ArrayManager<T>& manager, const std::string& name) {
    std::cout << "Array " << name << ": ";
    if (manager.isNull()) {
        std::cout << "(empty)" << std::endl;
        return;
    }
    std::cout << "[";
    for (size_t i = 0; i < manager.getSize(); ++i) {
        std::cout << manager[i];
        if (i < manager.getSize() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "] (size: " << manager.getSize() << ")" << std::endl;
}

// Helper function: create a test array
ArrayManager<int> createArray(int size) {
    std::cout << "\n=== Creating array with size " << size << " ===" << std::endl;
    int* arr = new int[size];
    for (int i = 0; i < size; ++i) {
        arr[i] = (i + 1) * 10;
    }
    return ArrayManager<int>(arr, size);
}

int main() {
    std::cout << "========== ArrayManager Test ==========\n" << std::endl;

    // Test 1: Default constructor
    std::cout << "--- Test 1: Default constructor ---" << std::endl;
    ArrayManager<int> am1;
    printArray(am1, "am1");
    std::cout << std::endl;

    // Test 2: Constructor taking raw pointer
    std::cout << "--- Test 2: Pointer constructor ---" << std::endl;
    int* testArr = new int[5] {10, 20, 30, 40, 50};
    ArrayManager<int> am2(testArr, 5);
    printArray(am2, "am2");
    std::cout << "Raw pointer: " << am2.get() << std::endl;
    std::cout << std::endl;

    // Test 3: get() function
    std::cout << "--- Test 3: get() function ---" << std::endl;
    int* rawPtr = am2.get();
    std::cout << "Raw pointer obtained: " << rawPtr << std::endl;
    std::cout << "First element via raw pointer: " << rawPtr[0] << std::endl;
    std::cout << "First element via ArrayManager: " << am2[0] << std::endl;
    std::cout << std::endl;

    // Test 4: Move constructor
    std::cout << "--- Test 4: Move constructor ---" << std::endl;
    ArrayManager<int> am3(std::move(am2));
    std::cout << "After move:" << std::endl;
    printArray(am2, "am2 (original)");
    printArray(am3, "am3 (new)");
    std::cout << std::endl;

    // Test 5: Move assignment operator
    std::cout << "--- Test 5: Move assignment ---" << std::endl;
    ArrayManager<int> am4;
    int* arrForAm4 = new int[3] {100, 200, 300};
    am4 = ArrayManager<int>(arrForAm4, 3);
    printArray(am4, "am4");

    ArrayManager<int> am5;
    am5 = std::move(am4);
    std::cout << "After move assignment:" << std::endl;
    printArray(am4, "am4 (original)");
    printArray(am5, "am5 (new)");
    std::cout << std::endl;

    // Test 6: swap() function
    std::cout << "--- Test 6: swap() function ---" << std::endl;
    int* arr1 = new int[4] {1, 2, 3, 4};
    int* arr2 = new int[6] {10, 20, 30, 40, 50, 60};
    ArrayManager<int> swap1(arr1, 4);
    ArrayManager<int> swap2(arr2, 6);

    std::cout << "Before swap:" << std::endl;
    printArray(swap1, "swap1");
    printArray(swap2, "swap2");

    swap1.swap(swap2);

    std::cout << "After swap:" << std::endl;
    printArray(swap1, "swap1");
    printArray(swap2, "swap2");
    std::cout << std::endl;

    // Test 7: release() function
    std::cout << "--- Test 7: release() function ---" << std::endl;
    int* arrForRelease = new int[3] {111, 222, 333};
    ArrayManager<int> am7(arrForRelease, 3);
    printArray(am7, "am7 (before release)");

    int* releasedPtr = am7.release();
    std::cout << "After release:" << std::endl;
    printArray(am7, "am7 (ownership released)");
    std::cout << "Released pointer address: " << releasedPtr << std::endl;
    std::cout << "First element of released pointer: " << releasedPtr[0] << std::endl;

    // Manually delete the released pointer
    delete[] releasedPtr;
    std::cout << "Manually released the returned pointer" << std::endl;
    std::cout << std::endl;

    // Test 8: Function return value (move semantics)
    std::cout << "--- Test 8: Function return value ---" << std::endl;
    ArrayManager<int> am8 = createArray(4);
    printArray(am8, "am8 (returned from function)");
    std::cout << std::endl;

    // Test 9: Different data type test
    std::cout << "--- Test 9: Double type test ---" << std::endl;
    double* doubleArr = new double[3] {1.1, 2.2, 3.3};
    ArrayManager<double> amDouble(doubleArr, 3);
    printArray(amDouble, "amDouble");
    std::cout << std::endl;

    // Test 10: Self-assignment test
    std::cout << "--- Test 10: Self-assignment test ---" << std::endl;
    ArrayManager<int> am9;
    int* arrForAm9 = new int[2] {99, 100};
    am9 = ArrayManager<int>(arrForAm9, 2);
    printArray(am9, "am9 (before self-assignment)");

    // This should be handled correctly by the move assignment operator
    am9 = std::move(am9);
    printArray(am9, "am9 (after self-assignment)");
    std::cout << std::endl;

    std::cout << "========== Test Complete ==========" << std::endl;
    std::cout << "\nNote: Destructors will now automatically release remaining resources" << std::endl;

    return 0;
}