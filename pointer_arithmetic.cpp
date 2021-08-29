#include <iostream>

using std::cout, std::endl;

int main(int argc, char const *argv[])
{
  int arr[5] = {1, 3, 5, 7, 9};
  // Decay to pointer
  int * arr_ptr = arr;
  for(int i = 0; i < 5; i++)
  {
    cout << "Pointer is " << arr_ptr << endl;
    cout << "Dereferenced " << *arr_ptr << endl;
    arr_ptr++;
    cout << "Incremented by one" << endl;
  }
}
