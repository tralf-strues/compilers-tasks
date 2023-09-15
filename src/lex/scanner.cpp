#include <lex/scanner.hpp>

namespace lex {

Scanner::Scanner(std::istream& source) {
  source.seekg(0, source.end);
  size_t size = source.tellg();
  source.seekg(0, source.beg);

  buffer_.resize(size);
  source.read(buffer_.data(), size);
}

const Location& Scanner::CurrentLocation() const {
  return current_location_;
}

char Scanner::CurrentSymbol() const {
  return buffer_[cur_offset_];
}

char Scanner::NextSymbol() const {
  return buffer_[cur_offset_ + 1];
}

void Scanner::MoveRight() {
  ++cur_offset_;
  ++current_location_.columnno;
}

void Scanner::MoveNextLine() {
  while (buffer_[cur_offset_++] != '\n') {;}

  ++current_location_.lineno;
  current_location_.columnno = 0;
}

size_t Scanner::CurrentOffset() const {
  return cur_offset_;
}

std::string_view Scanner::SubString(size_t start, size_t length) const {
  return std::string_view(buffer_).substr(start, length);
}

}  // namespace lex