#ifndef BASE_FILE_HPP
#define BASE_FILE_HPP

#include <ctime>

#include "string.hpp"

namespace vfs{
class base_file
{
  tm _create_time;
  tm _update_time;
  string _name;
public:
  base_file(const char* name);
private:
  void _on_update();
};
}

#endif//BASE_FILE_HPP
