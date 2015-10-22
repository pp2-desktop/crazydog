#include "cd_session.hpp"
#include "gpb/test.pb.h"

void cd_session::do_read_header() {
  name = "aa";
  auto self(shared_from_this());
  boost::asio::async_read(socket_,
			  boost::asio::buffer(read_msg_.data(), cd_message::header_length),
			  [this, self](boost::system::error_code ec, std::size_t)
			  {
			    std::cout << "[debug] do_read_header called" << std::endl;
			    if (!ec && read_msg_.decode_header()) {
			      do_read_body();
			    }
			    else {
			      std::cout << ec << std::endl;
			      std::cout << "[error] do_read_header 문제 발생" << std::endl;
			      self->destroy();
			      //room_.leave(shared_from_this());
			    }
			  });
}

void cd_session::do_read_body() {
  auto self(shared_from_this());
  boost::asio::async_read(socket_,
			  boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
			  [this, self](boost::system::error_code ec, std::size_t)
			  {
			    std::cout << "[debug] do_read_body called" << std::endl;

			    if (!ec) {
			      //room_.deliver(read_msg_);
			      // 패킷 처리해주고 다음 패킷을 위해서 버퍼 비워주기
			      //    header      |    1000    |   object  |
			      // | body? length | 4byte type |    gpb    |
			      //int type = 100;
			      //std::string packet = "abcd";
			      if(read_msg_.body_length() < sizeof(int)) {
				self->destroy();
			      }

			      int type = -1;
			      std::memcpy(&type, read_msg_.get_type(), read_msg_.get_type_size());
			      std::string packet(read_msg_.get_payload(), read_msg_.get_payload_size());

			      bool r = self->handle(type, packet);
			      if(!r) {
				std::cout << "[error] 패킷 파싱중 문제 발생" << std::endl;
				self->destroy();				
			      }

			      do_read_header();
			    }
			    else {
			      std::cout << "[error] do_read_body 문제 발생" << std::endl;
			      self->destroy();
			      //room_.leave(shared_from_this());
			    }
			  });
}


void cd_session::do_write(int type, std::string packet) {

  char data[cd_message::header_length + cd_message::max_body_length] = {0, };
 int len = sizeof(int) *2 + packet.size();

 std::memcpy(data, &len, sizeof(int));
 std::memcpy(data+sizeof(int), &type, sizeof(int));
 std::memcpy(data+(sizeof(int)*2), packet.c_str(), packet.size());

 auto self(shared_from_this());
 boost::asio::async_write(socket_,
			  boost::asio::buffer(data,
					      len),
			  [this, self] (boost::system::error_code ec, std::size_t len)
			  {
			    if (!ec) {
				std::cout << "[debug] 전송 완료" << std::endl;
				std::cout << "[debug] 보낸 패킷 길이: " << len << std::endl;
			      }
			    else {
				std::cout << "[error] 전송 실패" << std::endl;
				self->destroy();
				//room_.leave(shared_from_this());
			      }
			  });
}

/*
std::pair<int, std::string> cd_session::do_read_packet(int len, char* buf) {

  int type = -1;
  std::string packet("");

  std::memcpy(&type, buf, sizeof(int));
  std::cout << "[debug] 패킷타입: " << type << std::endl;

  buf = buf + sizeof(int);
  len = len - sizeof(int);
  std::memcpy(&packet, buf, len);

  std::cout << "xxxxxxxxxxxxxxxxxxxxx" << std::endl;

  Person cp;
  bool r = cp.ParseFromString(packet);

  std::cout << "deserialized result: " << r << std::endl;

  std::cout << "age: " << cp.age() << std::endl;
  std::cout << "name: " << cp.name() << std::endl;

  for(int i=0; i < cp.friends_size(); i++) {
    std::cout << "friends num: " << cp.friends(i) << std::endl;
  }


  return std::make_pair(type, packet);
}
*/


			      /*
			      char tmp[512] = {0,};
			      std::string packet("");
			      Person p;
			      p.set_age(20);
			      p.set_name("hello");
			      p.add_friends(5);
			      p.add_friends(10);
			      p.add_friends(15);
			      p.SerializeToString(&packet);
			      std::cout << "byte size: " << p.ByteSize() << std::endl;
			      int type = 100;
			      memcpy(tmp, &type, sizeof(int));
			      memcpy(tmp+sizeof(int), &packet, p.ByteSize());
			      std::pair<int, std::string> rtn = do_read_packet(sizeof(int)+p.ByteSize(), tmp);
*/
