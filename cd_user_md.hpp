#ifndef CD_USER_MD_HPP
#define CD_USER_MD_HPP

#include <map>
#include "cd_user.hpp"

class cd_user_md {
public:  
  bool connected(std::shared_ptr<cd_user>);
  bool disconnected(std::shared_ptr<cd_user>);

  static cd_user_md& instance() {
    static cd_user_md obj;
    return obj;
  }

  void init() {

  }

  std::map<cd_user*, cd_user_ptr> m;
};

#endif
