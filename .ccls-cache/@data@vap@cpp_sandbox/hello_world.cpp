#include <iostream>
#include <vector>
using std::vector;

template <typename T>
T takeGreater(T a, T b) {
  return a < b ? b : a;
};

class givesInt {
  public:
    int virtual giveMeAnInt()
    {
      return 0;
    }
};

class giveTen: givesInt {
  public:
    int theInt;
    giveTen(int a){ this->theInt = a; };
    int giveMeAnInt() override
    {
      return theInt;
    }
};

int main() {
  vector<int> v {1,2,3};
  int v_len = v.size();
  std::cout << v_len << "\n";
  vector<int> w(v_len+1);
  for (int i = 0; i < v_len; ++i) { 
    w[i] = v[i];
  }
  w[v_len] = 4;
  for(auto i:w) std::cout << i << ' ';
}
