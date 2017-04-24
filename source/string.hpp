#ifndef STRING_HPP
#define STRING_HPP

#include <iostream>

#define ALOC_SIZE 32
#define COMPACT true

namespace vfs{
class string
{
  int _capacity;
  int _size;
  char* _string;

public:
  string(int to_reserve = ALOC_SIZE);
  string(const string& other);
  string& operator=(const string& other);
  string(string&& other);
  string& operator=(string&& other);
  ~string();

  string(const char* str, bool compact = false);

  int size() const;

  void shrink();

  operator const char*() const;
  string operator+(const char* str) const;
  string& operator+=(const char* str);
  string& operator+=(const char symbol);

private:
  void _destroy();
  bool _has_space_for(int len) const;
  void _resize_up();
};
}

std::istream& operator>>(std::istream& input, vfs::string str);

#endif//STRING_HPP
