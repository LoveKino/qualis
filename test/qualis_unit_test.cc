#include <iostream>
#include <assert.h>

using namespace std;
#include "../src/qualis.h"

int main() {
  try {
    cout << "[qualis::parseText]" << endl;
    auto real = qualis::parseText("" ,  qualis::ParseOption() );
    auto expect =  vector<qualis::TestUnit>();
    assert(real == expect);
  } catch(const exception& e) {
    throw "Fail to run test unit: qualis::parseText";
  }
}