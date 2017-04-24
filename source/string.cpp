#include <cstring>
#include <climits>

#include "string.hpp"

using namespace vfs;

string::string(int to_reserve)
  : _capacity(to_reserve), _size(0), _string(nullptr)
{
  _string = new char[_capacity];
}

string::string(const string& other)
  : _capacity(other._capacity), _size(other._size)
{
  _string = new char [_capacity];
  memcpy(_string, other._string, _size + 1);
}

string& string::operator= (const string& other)
{
  if(this != &other){
    if(_capacity < other._size + 1){
      _capacity = other._capacity;
      _destroy();
      _string = new char [_capacity];
    }
    _size = other._size;
    memcpy(_string, other._string, _size + 1);
  }
  return *this;
}

string::string(string&& other)
  : _capacity(other._capacity), _size(other._size), _string(other._string)
{
  other._string = nullptr;
}

string& string::operator= (string&& other)
{
  if(this != &other){
    _capacity = other._capacity;
    _size = other._size;
    _string = other._string;
    other._string = nullptr;
  }
  return *this;
}

string::~string()
{
  _destroy();
}

string::string(const char* str, bool compact)
{
  int _size = strlen(str);
  if(compact){
    _capacity = _size + 1;
  }
  else {
    _capacity = ((_size + 1)/ALOC_SIZE + 1)*ALOC_SIZE;
  }
  _string = new char [_capacity];
  memcpy(_string, str, _size + 1);
}

int string::size() const
{
  return _size;
}

void string::shrink()
{
  if(_capacity > _size + 1){
    _capacity = _size + 1;
    char* tmp = new char[_capacity];
    memcpy(tmp, _string, _size);
    delete[] _string;
    _string = tmp;
  }
}

string::operator const char*() const
{
  return _string;
}

string string::operator+(const char* str) const
{
  int len = strlen(str);
  string return_str(_size + len + 1);
  return_str._size = return_str._capacity - 1;
  memcpy(return_str._string, _string, _size);
  memcpy(return_str._string + _size, str, len + 1);
  return return_str;
}

string& string::operator+=(const char* str)
{
  int len = strlen(str);
  if(!_has_space_for(len)){
    _capacity = ((_size + len + 1)/ALOC_SIZE + 1)*ALOC_SIZE;
    char* tmp = new char[_capacity];
    memcpy(tmp, _string, _size);
    delete[] _string;
    _string = tmp;
  }
  memcpy(_string + _size, str, len + 1);
  _size += len;
  return *this;
}

string& string::operator+=(const char sym)
{
  if(_size + 1 >= _capacity){
    _resize_up();
  }
  _string[_size] = sym;
  _string[++_size] = 0;
  return *this;
}

//PRIVATE

void string::_destroy()
{
  delete[] _string;
  _string = nullptr;
}

bool string::_has_space_for(int len) const
{
  return len + _size < _capacity;
}

void string::_resize_up()
{
  _capacity += ALOC_SIZE;
  char* tmp = new char[_capacity];
  memcpy(tmp, _string, _size + 1);
  delete[] _string;
  _string = tmp;
}

//NONMEMBER

std::istream& operator>>(std::istream& input, string str)
{
  char sym;
  input.get(sym);
  std::cout<<sym;
  while(isgraph(sym) && !isspace(sym)){
    str += sym;
    input.get(sym);
    std::cout<<sym;
  }
  return input;
}
