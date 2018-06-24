#pragma once

#include <iostream>
#include <vector>

using namespace std;

namespace cpp_qualis_case_converter {
    string convertCase(string fun_invoke, vector<string> params);
    string mergeCaseCode(vector<string> caseCodeList);
}
