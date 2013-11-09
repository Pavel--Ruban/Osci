#include <iostream>

class abc {
  public:
    int mm() {
      return 2;
    }
    int lc () {
      return mm();
    }
};

int main (int a, char **v) {
  abc *x;
  std::cout << "result: " << x->lc();

  return 0;
}
