#include <iostream>
#include <assert.h>

using namespace std;
#include "../src/qualis.h"

int main() {
  try {
    cout << "start to run test for: qualis::parseText" << endl;
    auto real = qualis::parseText("//#add\n//#1|2|3" ,  qualis::ParseOption() );
    auto expect =  vector<qualis::TestUnit>();
    assert(real == expect);
  } catch(const exception& e) {
    throw "Fail to run test unit: qualis::parseText";
  }
}