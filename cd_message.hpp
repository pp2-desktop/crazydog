#ifndef CD_MESSAGE_HPP
#define CD_MESSAGE_HPP

#include <cstdio>
#include <cstdlib>
#include <cstring>

class cd_message
{
public:
  enum { header_length = sizeof(int) };
  enum { max_body_length = 512 };

  cd_message()
    : body_length_(0) {
  }

  /*
  const char* data() const {
    return data_;
  }
*/

  char* data() {
    return data_;
  }

  std::size_t length() const {
    return header_length + body_length_;
  }

  /*
  const char* body() const {
    return data_ + header_length;
  }
  */

  char* body() {
    return data_ + header_length;
  }

  std::size_t body_length() const {
    return body_length_;
  }

  char* get_type() {
    return data_ + header_length;
  }

  char* get_payload() {
    return data_ + header_length + sizeof(int);
  }

  int get_type_size() {
    return sizeof(int);
  }

  int get_payload_size() {
    return body_length_ - sizeof(int);
  }
  /*
  void body_length(std::size_t new_length) {
    body_length_ = new_length;
    if (body_length_ > max_body_length)
      body_length_ = max_body_length;
  }
  */

  bool decode_header() {
    std::cout << "[debug] decode_header called" << std::endl;


    std::memcpy(&body_length_, data_, sizeof(int));
    body_length_ = body_length_ - sizeof(int);

    std::cout << "[debug] body길이: " << body_length_ << std::endl;

    if(body_length_ > max_body_length) {
      body_length_ = 0;
      return false;
    }

    return true;
  }

  /*
  void encode_header()
  {
    char header[header_length + 1] = "";
    std::sprintf(header, "%4d", body_length_);
    std::memcpy(data_, header, header_length);
  }
*/

  //private:
  char data_[header_length + max_body_length];
  int body_length_;
};

#endif // CHAT_MESSAGE_HPP
