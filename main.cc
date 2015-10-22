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
#include <signal.h>
#include "cd_server.hpp"
#include "cd_handler.hpp"
cd_server* s;
void run_cd_server() {
  //boost::asio::io_service io_service;
  tcp::endpoint endpoint(tcp::v4(), 8080);
  s = new cd_server(endpoint);

  std::vector<std::thread> workers;

  for (int j = 0; j < 8; ++j) {
    workers.push_back(std::thread([&]() {
	  std::cout << "j: " << j << std::endl;
	  s->io_service_.run();
	}));
  }
  for(std::thread& t : workers) {
    t.join();
  }

  delete s;
}

void sigint(int a) {
  std::cout << "signal" << std::endl;
  s->io_service_.stop();
}

int main(int argc, char* argv[])
{
  try
  {
    std::cout << " aaa" << std::endl;
    if(!cd_handler::instance().init()) {
      std::cout << "[error] cd_handler init 실패" << std::endl;
      return 1;
    }
   
//boost::asio::io_service io_service;
    std::thread t(run_cd_server);
    
    signal(SIGINT, sigint);


    t.join();

    std::cout << " bbb" << std::endl;
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }
  std::cout << "ccc" << std::endl;
  return 0;
}
