#ifndef CD_USER_HPP
#define CD_USER_HPP

#include "cd_session.hpp"
using boost::asio::ip::tcp;

class cd_user;
typedef std::shared_ptr<cd_user> cd_user_ptr;

class cd_user
  : public cd_session
{
public:
  cd_user(boost::asio::io_service& io_service);
  virtual ~cd_user();

  void destroy();
  void check();
  bool handle(int type, std::string packet);
  
  int recv_cnt;
private:
  boost::asio::io_service& io_service_;
};


#endif
