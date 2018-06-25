#include "cpp.h"
#include <iostream>

namespace cpp_qualis_case_converter {
    string convertCase(string fun_invoke, vector<string> params) {
        string code = fun_invoke; 
        code += "(";

        unsigned int len = params.size();
        for(unsigned int i = 0; i < len - 1; i++) {
            code += params[i];
            if(i != len - 2) {
                code += ", ";
            }
        }

        code += ")";

        code = "  try {\n"
          "    cout << \"start to run test for: " + fun_invoke + "\" << endl;\n"
          "    auto real = " + code + ";\n"
          "    auto expect = " + params[len -1] + ";\n"
          "    assert(real == expect);"
          "\n  }"
          " catch(const exception& e) {\n"
          "    throw \"Fail to run test unit: " + fun_invoke + "\";"
          "\n  }";
        return code;
    }

    string mergeCaseCode(vector<string> caseCodeList, string setup) {
        string code = "";
        for(auto const &caseCode: caseCodeList) {
            code += code == ""? caseCode: "\n" + caseCode;
        }

        code = "#include <iostream>\n"
            "#include <assert.h>\n\n"
            "using namespace std;\n"
            "" + setup + "\n\n"
            "int main() {\n" + code + ""
            "\n}";
        return code;
    }
}
