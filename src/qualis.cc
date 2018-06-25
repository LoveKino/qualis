#include "qualis.h"
#include <fstream>

namespace qualis {
    namespace {
        /**
         * seperate parts by delimiter
         */
        vector<string> parseLine(const string text, int lineStartIndex, int lineEndIndex, const char delimiter) {
            unsigned int i = lineStartIndex;
            vector<string> parts;
            unsigned int partStartIndex = lineStartIndex;

            while(i <= lineEndIndex) {
                if(text[i] == '\\') {
                    i += 2;
                } else if(text[i] == delimiter) {
                    int partLen = i - partStartIndex;
                    parts.push_back(partLen < 0? "": text.substr(partStartIndex, partLen));
                    partStartIndex = i + 1;
                    i++;
                } else {
                    i++;
                }
            }

            int partLen = lineEndIndex - partStartIndex + 1;
            parts.push_back(partLen < 0? "": text.substr(partStartIndex, partLen));

            return parts;
        }

        vector<TestUnit> parsePartsList(vector<vector<string>> partsList) {
            unsigned int i = 0;
            unsigned int len = partsList.size();

            vector<TestUnit> testUnits;

            string cur_fun_invoke = "";

            while(i < len) {
              vector<vector<string>> curCaseList;

              while(i < len) {
                  const vector<string> parts = partsList[i];

                  if(parts.size() == 1) {
                      if(cur_fun_invoke != "") {
                          testUnits.push_back(TestUnit(cur_fun_invoke, curCaseList));
                      }
                      cur_fun_invoke = parts[0];
                      i++;
                      break;
                  } else if(parts.size() > 1) {
                      if(cur_fun_invoke == "") {
                          throw "missing function invoke line.";
                      }
                      curCaseList.push_back(parts);
                      i++;

                      if(i >= len) {
                        if(cur_fun_invoke != "") {
                            testUnits.push_back(TestUnit(cur_fun_invoke, curCaseList));
                        }
                      }
                  }
              }
            }

            return testUnits;
        }
    }

    bool TestUnit::operator== (const TestUnit &a) const {
        return this -> caseList == a.caseList && this -> caseList == a.caseList;
    }

    vector<TestUnit> parseText(const string text, const ParseOption parseOption) {
        unsigned int txtLen = text.length();
        unsigned int i = 0;
        string prefix = parseOption.lineRegPrefix;
        unsigned int prefixLen = prefix.length();

        vector<vector<string>> partsList;

        while(i < txtLen) {
            if(text[i] == ' ' || text[i] == '\t' || text[i] == '\f') {
                i++;
            } else if(text.substr(i, prefixLen) == prefix) {
                i += prefixLen;
                int lineStartIndex = i;
                while(i < txtLen && text[i] != '\n') {
                    i++;
                }
                int lineEndIndex = i - 1;

                auto parts = parseLine(text, lineStartIndex, lineEndIndex, parseOption.delimiter);
                partsList.push_back(parts);
                i++;
            } else {
                i += prefixLen;
                while(i < txtLen && text[i] != '\n') {
                    i++;
                }
                i++;
            }
        }

        return parsePartsList(partsList);
    }

    vector<TestUnit> parseFile(const string filePath, const ParseOption parseOption) {
        ifstream input(filePath);
        vector<vector<string>> partsList;

        string prefix = parseOption.lineRegPrefix;
        unsigned int prefixLen = prefix.length();

        for(string line; getline(input, line);) {
            unsigned int start = 0;
            while(start < line.size() &&
                    (line[start] == ' ' || line[start] == '\t' || line[start] == '\f')) {
                start ++;
            }

            if(start < line.size() && line.substr(start, prefixLen) == prefix) {
              auto parts = parseLine(line, start + prefixLen, line.length() - 1, parseOption.delimiter);
              partsList.push_back(parts);
            }
        }

        return parsePartsList(partsList);
    }

    string generateTestCode(vector<TestUnit> testUnits,
            string (*caseConverter)(string, vector<string>),
            string (*caseCodeMerger)(vector<string>, string),
            string setup) {
        vector<string> caseCodeList;

        for(auto const& testUnit: testUnits) {
            string fun_invoke = testUnit.fun_invoke;

            for(auto const& params: testUnit.caseList) {
                string caseCode = (*caseConverter)(fun_invoke, params);
                caseCodeList.push_back(caseCode);
            }
        }

        return (*caseCodeMerger)(caseCodeList, setup);
    }

    void saveTestCodeToFile(string testCode, string filePath) {
        ofstream file;
        file.open(filePath);
        file << testCode;
        file.close();
    }
}
