#include <memory>
#include "cd_user.hpp"
#include "cd_user_md.hpp"
#include "cd_handler.hpp"

cd_user::cd_user(boost::asio::io_service& io_service) : cd_session(io_service), io_service_(io_service) {
  std::cout << "cd_user called" << std::endl;
  recv_cnt = 0;
}

cd_user::~cd_user() {

}

void cd_user::destroy() {
  std::cout << "cd_user destroy called" << std::endl;

  auto self(std::dynamic_pointer_cast<cd_user>(shared_from_this()));

  
  bool r = cd_user_md::instance().disconnected(self);
  if(r) {
    boost::system::error_code ec;
    socket_.shutdown(boost::asio::socket_base::shutdown_both, ec);
    socket_.close(ec);
    std::cout << "[debug] 유저 삭제에 관련해서 나머지 정리" << std::endl;
  }

}

void cd_user::check() {
  std::cout << "check" << std::endl;
}

bool cd_user::handle(int type, std::string packet) {
  std::cout << "[debug] cd_user handle called" << std::endl;
  auto self(std::dynamic_pointer_cast<cd_user>(shared_from_this()));

  bool r = cd_handler::instance().handle(type, self, packet);

  if(!r) {
    
  }

  return true;
}
