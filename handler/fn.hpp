#ifndef FN_HPP
#define FN_HPP

#include "../cd_user.hpp"

enum packet { get_user_info_fn = 100, set_user_info_fn };

bool get_user_info(cd_user_ptr user, std::string packet);
bool set_user_info(cd_user_ptr user, std::string packet);


#endif
