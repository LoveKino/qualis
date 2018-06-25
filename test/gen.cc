#include <iostream>
#include <assert.h>

using namespace std;
#include "./test.h"

int main() {
  try {
    cout << "start to run test for: add" << endl;
    assert(add(1, 2) == 3);
  } catch(const exception& e) {
    throw "Fail to run test unit: add";
  }
}