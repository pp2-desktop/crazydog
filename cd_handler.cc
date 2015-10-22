#include <utility>
#include "cd_handler.hpp"
#include "handler/fn.hpp"

cd_handler::cd_handler() {

}

cd_handler::~cd_handler() {

}

bool cd_handler::add_handle(cb fn) {

  return true;
}

bool cd_handler::handle(int type, cd_user_ptr p, std::string packet) {

  if ( m.find(type) == m.end() ) {
    std::cout << "[error] 핸들러를 찾을수 없음" << std::endl;
    return false;
  }

  bool r = m[type](p, packet);

  if(!r) {
    std::cout << "[error] 핸들러 로직 처리중 문제 발생" << std::endl;
  }

  std::cout << "[debug] 핸들러 처리 완료" << std::endl;

  return true;
}



bool cd_handler::init() {

  bool r = true;
  r &= m.insert(std::make_pair(packet::get_user_info_fn, get_user_info)).second;
  r &= m.insert(std::make_pair(packet::set_user_info_fn, set_user_info)).second;

  std::cout << "[debug] packet handler size: " << m.size() << std::endl;
  return r;
}
