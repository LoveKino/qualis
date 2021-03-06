#include <iostream>
#include "qualis.h"
#include "./translator/cpp.h"

using namespace std;
using namespace qualis;

int main() {
    // auto testUnits = parseText("//#add\n//#1|2|3\n//#succ\n//#1|2", ParseOption());
    auto testUnits = parseFile("./src/qualis.h", ParseOption());
    auto text = generateTestCode(testUnits,
            &cpp_qualis_case_converter::convertCase,
            &cpp_qualis_case_converter::mergeCaseCode,
            "#include \"../src/qualis.h\"");
    saveTestCodeToFile(text, "./test/qualis_unit_test.cc");
    return 0;
}
