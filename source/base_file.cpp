#include <ctime>

#include "base_file.hpp"

using namespace vfs;

base_file::base_file(const char* name)
  :_name(name)
{
  time_t raw_time = time(0);
  _create_time = _update_time = *localtime(&raw_time);
}

void base_file::_on_update()
{
  time_t raw_time = time(0);
  _update_time = *localtime(&raw_time);
}
