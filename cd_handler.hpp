#ifndef CD_HANDLER_HPP
#define CD_HANDLER_HPP

#include <functional>
#include <string>
#include <map>
#include "cd_user.hpp"

typedef std::function<bool(cd_user_ptr, std::string)> cb;
class cd_handler {
public:
  cd_handler();
  ~cd_handler();

  static cd_handler& instance() {
    static cd_handler obj;
    return obj;
  }

  bool handle(int type, cd_user_ptr p,  std::string packet);

  bool init();

private:
  bool add_handle(cb);
  std::map<int, cb> m;
};


#endif
