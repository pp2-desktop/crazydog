#ifndef CD_SESSION_HPP
#define CD_SESSION_HPP

#include <cstdlib>
#include <deque>
#include <iostream>
#include <list>
#include <memory>
#include <set>
#include <utility>
#include <boost/asio.hpp>
#include "cd_message.hpp"

using boost::asio::ip::tcp;

class cd_session;
typedef std::shared_ptr<cd_session> cd_session_ptr;

class cd_session
  : public std::enable_shared_from_this<cd_session> {

public:
  cd_session(boost::asio::io_service& io_service) : socket_(io_service) {
    std::cout << "cd_session called" << std::endl;
  }

  void start()
  {
    //room_.join(shared_from_this());
    std::cout << "cd_session start called" << std::endl;
    do_read_header();
  }

  /*
  void deliver(const chat_message& msg)
  {
    bool write_in_progress = !write_msgs_.empty();
    write_msgs_.push_back(msg);
    if (!write_in_progress)
    {
      do_write();
    }
  }
  */
  
  virtual void destroy()=0;
  virtual void check()=0;
  virtual bool handle(int type, std::string packet)=0;

private:
  void do_read_header();
  void do_read_body();
  //std::pair<int, std::string> do_read_packet(int len, char* buf);
  /*
  void do_write()
  {
    auto self(shared_from_this());
    boost::asio::async_write(socket_,
        boost::asio::buffer(write_msgs_.front().data(),
          write_msgs_.front().length()),
        [this, self](boost::system::error_code ec, std::size_t)
        {
          if (!ec)
          {
            write_msgs_.pop_front();
            if (!write_msgs_.empty())
            {
              do_write();
            }
          }
          else
          {
            room_.leave(shared_from_this());
          }
        });
  }
*/
public:
  tcp::socket socket_;
//chat_room& room_;
  cd_message read_msg_;
  std::string name;
//chat_message_queue write_msgs_;
};

#endif
