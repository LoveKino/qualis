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

        code = "assert(" + code + ") == " + params[len - 1] + ");";
        return code;
    }

    string mergeCaseCode(vector<string> caseCodeList) {
        string code = "";
        for(auto const &caseCode: caseCodeList) {
            code += code == ""? caseCode: "\n" + caseCode;
        }
        return code;
    }
}
