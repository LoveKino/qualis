#include <iostream>
#include "qualis.h"
#include "./translator/cpp.h"

using namespace std;
using namespace qualis;

int main() {
    auto testUnits = parseText("//#add\n//#1|2|3\n//#succ\n//#1|2", ParseOption());
    auto text = generateTestCode(testUnits, &cpp_qualis_case_converter::convertCase, &cpp_qualis_case_converter::mergeCaseCode);
    cout << text << endl;
    return 0;
}
