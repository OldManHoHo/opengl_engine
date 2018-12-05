#include "TGLUDPInterface.h"

TGLUDPInterface::TGLUDPInterface()
{
	
}

bool TGLUDPInterface::init(std::string ip_address, int port)
{
	my_address = new sockaddr_in;
	my_address->sin_family = AF_INET;
	my_address->sin_port = htons(port);	
	inet_aton(ip_address.c_str(), &my_address->sin_addr);
	sock = socket(AF_INET, SOCK_DGRAM, 0);	
	bind(sock, (struct sockaddr *)my_address, sizeof(my_address));
}

int TGLUDPInterface::send_msg(std::vector<uint8_t> in_msg, sockaddr_in * to_addr)
{

	return sendto(sock, &in_msg[0], in_msg.size(), 0,
              (struct sockaddr *)to_addr, sizeof(*to_addr));

}

std::vector<uint8_t> TGLUDPInterface::receive_msg(sockaddr_in * from_addr)
{
	std::vector <uint8_t> out_vec(max_msg_size);
	socklen_t out_size;
	recvfrom(sock, &out_vec[0], max_msg_size, 0, (struct sockaddr *)from_addr, &out_size);
}

void TGLUDPInterface::start_receive_thread()
{
	receive_thread = new std::thread([&] (TGLUDPInterface * player) { player->receive_loop(); }, this);	
		
}

void TGLUDPInterface::receive_loop()
{
	while(1)
	{
		std::vector <uint8_t> rec_msg;
		sockaddr_in * from_addr;
		rec_msg = receive_msg(from_addr);
		msg_queue_mutex.lock();
		msg_queue.push_back(rec_msg);
		msg_queue_mutex.unlock();
	}
}

std::vector <uint8_t> TGLUDPInterface::pop_msg()
{
	std::vector <uint8_t> out_vector;
	msg_queue_mutex.lock();
	out_vector = msg_queue.front();
	msg_queue_mutex.unlock();
	return out_vector;
}

int main()
{
	TGLUDPInterface udp_int;
	udp_int.init("localhost", 12345);
}
