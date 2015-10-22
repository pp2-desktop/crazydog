#include "fn.hpp"
#include "../gpb/test.pb.h"

bool get_user_info(cd_user_ptr user, std::string packet) {
  std::cout << "[debug] get_user_info called" << std::endl;

  Person cp;
  bool r = cp.ParseFromString(packet);

  std::cout << "deserialized result: " << r << std::endl;

  std::cout << "age: " << cp.age() << std::endl;
  std::cout << "name: " << cp.name() << std::endl;

  for(int i=0; i < cp.friends_size(); i++) {
    std::cout << "friends num: " << cp.friends(i) << std::endl;
  }

  std::cout << "user recv_cnt: " << user->recv_cnt << std::endl;
  user->recv_cnt++;
  

  return true;
}
