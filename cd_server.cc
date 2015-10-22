#include "cd_server.hpp"

void cd_server::do_accept() {
  std::cout << "[debug] do_accept start" << std::endl;

  std::cout << "[debug] 접속 대기" << std::endl;
  acceptor_.async_accept(p->socket_,
			 [this](boost::system::error_code ec)
			 {
			   if (!ec) {
			     std::cout << "[debug] 유저 접속" << std::endl;

			     cd_user_md::instance().connected(p);

			     //std::pair<std::map<cd_user*, cd_user_ptr>::iterator, bool> r = cd_user_md::instance().users.insert(std::pair<cd_user*, cd_user_ptr>(p.get(), p));

			     p->start();

			     //std::cout << "result: " << r.second << std::endl;
			     p.reset(new cd_user(io_service_));
	    

			     //std::make_shared<chat_session>(std::move(socket_), room_)->start();
			   } else {
			     std::cout << "[error] 접속 실패" << std::endl;
			   }

			   do_accept();
			 });

  std::cout << "[debug] do_accept end" << std::endl;
}
