#include <memory>
#include <utility>
#include "cd_user_md.hpp"

bool cd_user_md::connected(std::shared_ptr<cd_user> p) {
  
  bool r = m.insert(std::make_pair(p.get(), p)).second;
  if(r) {
    std::cout << "[debug] 유저 삽입 성공" << std::endl;
  } else {
    std::cout << "[error] 유저 삽입 실패" << std::endl;
  }
 

  return true;
}

bool cd_user_md::disconnected(std::shared_ptr<cd_user> p) {
  p->check();

  bool r = m.erase(p.get());
  if(r) {
    std::cout << "[debug] 유저 삭제 성공" << std::endl;
  } else {
    std::cout << "[error] 유저 삭제 실패" << std::endl;
  }

  return true;
}
