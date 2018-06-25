#pragma once

#include <iostream>
#include <vector>

using namespace std;

/**
 * read specifics from file and generate corresponding testing code
 *
 * 1. parse file text to testing specific structure
 *
 * 2. generate testing code from testing specific structure
 */
namespace qualis {
    class ParseOption {
        public:
            const string lineRegPrefix;
            const char delimiter;
            ParseOption(const string lRP = "//#", const char _delimiter = '|'): lineRegPrefix(lRP), delimiter(_delimiter) {}
    };

    class TestUnit {
        public:
            const string fun_invoke;
            const vector<vector<string>> caseList;
            TestUnit(const string _fun_invoke, const vector<vector<string>> _caseList): fun_invoke(_fun_invoke), caseList(_caseList) {}
            bool operator == (const TestUnit &a) const; 
    };

    vector<TestUnit> parseFile(const string filePath, const ParseOption parseOption);

    /**
     * @param text: source string
     */
    //#qualis::parseText
    //#"//#add\n//#1\|2\|3" | qualis::ParseOption() | vector<qualis::TestUnit>()
    vector<TestUnit> parseText(const string text, const ParseOption parseOption);

    /**
     * translate test specific to target unit test code
     */
    string generateTestCode(vector<TestUnit> testUnits,
            string (*caseConverter)(string, vector<string>),
            string (*caseCodeMerger)(vector<string>, string),
            string setup);

    void saveTestCodeToFile(string testCode, string filePath);
}
