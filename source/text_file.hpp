#ifndef TEXT_FILE_HPP
#define TEXT_FILE_HPP

#include <string>

#include "base_file.hpp"

namespace vfs{
class text_file: public base_file
{
  std::string _text;
public:
  text_file(const char* name, const char* text = "");

  const std::string& get_text() const;

  void set_text(const char* new_text);
  void append_text(const char* text_to_append);
  void overwrite_text(const char* text, int position);
  void insert_text(const char* text, int position);
};
}

#endif//TEXT_FILE_HPP
