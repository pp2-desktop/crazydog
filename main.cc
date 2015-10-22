//----------------------------------------------------------------------

//typedef std::deque<cd_message> cd_message_queue;

//----------------------------------------------------------------------

//----------------------------------------------------------------------

/*lass chat_room
{
public:
  void join(chat_participant_ptr participant)
  {
    participants_.insert(participant);
    for (auto msg: recent_msgs_)
      participant->deliver(msg);
  }

  void leave(chat_participant_ptr participant)
  {
    participants_.erase(participant);
  }

  void deliver(const chat_message& msg)
  {
    recent_msgs_.push_back(msg);
    while (recent_msgs_.size() > max_recent_msgs)
      recent_msgs_.pop_front();

    for (auto participant: participants_)
      participant->deliver(msg);
  }

private:
  std::set<chat_participant_ptr> participants_;
  enum { max_recent_msgs = 100 };
  chat_message_queue recent_msgs_;
};
*/


#include <thread>
#include <vector>
#include <functional>
#include "cd_server.hpp"
#include "cd_handler.hpp"

int main(int argc, char* argv[])
{
  try
  {
    boost::asio::io_service io_service;
    tcp::endpoint endpoint(tcp::v4(), 8080);
    std::cout << " aaa" << std::endl;
    if(!cd_handler::instance().init()) {
      std::cout << "[error] cd_handler init 실패" << std::endl;
      return 1;
    }
    cd_server* s = new cd_server(io_service, endpoint);

    std::vector<std::thread> workers;

    for (int j = 0; j < 8; ++j) {
      workers.push_back(std::thread([&]() {
	    std::cout << "j: " << j << std::endl;
	    io_service.run();
	  }));
    }
    for(std::thread& t : workers) {
      t.join();
    }
 //std::bind(&boost::asio::io_service::run, &io_service);


    
    io_service.run();
    delete s;
    std::cout << " bbb" << std::endl;
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }
  std::cout << "ccc" << std::endl;
  return 0;
}
