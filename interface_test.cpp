#include <string>
#include <iostream>

int main() 

{
  std::string is_str1 = "is string";
  std::string is_str2 = "is another string";
  std::string* pt1 = &is_str1;
  std::string* pt2 = &is_str2;
  std::cout << *pt1;
  std::cout << pt2;
}
