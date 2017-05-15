#include <cstring>

#include "text_file.hpp"

using namespace vfs;

text_file::text_file(const char* name, const char* text)
  :base_file(name), _text(text)
{
}

const std::string& text_file::get_text() const
{
  return _text;
}

void text_file::set_text(const char* new_text)
{
  _text = new_text;
  _on_update();
}

void text_file::append_text(const char* text_to_append)
{
  _text += text_to_append;
  _on_update();
}

void text_file::overwrite_text(const char* text, int pos)
{
  size_t len = strlen(text);
  size_t second_start = len + pos;
  if(second_start <= _text.size()){
    _text = _text.substr(0, pos) + std::string(text) +
      _text.substr(second_start);
  }
  else{
    _text = _text.substr(0, pos) + std::string(text);
  }
  _on_update();
}

void text_file::insert_text(const char* text, int pos)
{
  _text = _text.substr(0, pos) + std::string(text) +
    _text.substr(pos);
  _on_update();
}
