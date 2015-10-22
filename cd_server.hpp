#ifndef CD_SERVER_HPP
#define CD_SERVER_HPP

#include "cd_user_md.hpp"

class cd_server
{
public:

  /*
  cd_server(boost::asio::io_service& io_service,
      const tcp::endpoint& endpoint)
    : acceptor_(io_service, endpoint), io_service_(io_service) {

    cd_user_md::instance().init();
    p = std::make_shared<cd_user>(io_service);
    do_accept();
  }
  */

  cd_server(const tcp::endpoint& endpoint)
    : acceptor_(io_service_, endpoint) {

    cd_user_md::instance().init();
    p = std::make_shared<cd_user>(io_service_);
    do_accept();
  }


  void run();

  boost::asio::io_service io_service_;
private:
  void do_accept();

  tcp::acceptor acceptor_;
  //boost::asio::io_service& io_service_;

  cd_user_ptr p;
  //std::map<int, cd_user> users_;
  //chat_room room_;
};

#endif
