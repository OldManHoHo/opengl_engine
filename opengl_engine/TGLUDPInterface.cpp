#include "TGLUDPInterface.h"
#include <unistd.h>
#include <iostream>

TGLUDPInterface::TGLUDPInterface()
{
	
}

bool TGLUDPInterface::init(std::string ip_address, int port)
{
	int retval = 0;
	my_address.sin_family = AF_INET;
	my_address.sin_port = htons(port);	
	inet_aton(ip_address.c_str(), &my_address.sin_addr);
	sock = socket(AF_INET, SOCK_DGRAM, 0);	
	retval = bind(sock, (sockaddr *)&my_address, sizeof(my_address));
	return retval;
}

int TGLUDPInterface::send_msg(std::vector<uint8_t> in_msg, sockaddr_in * to_addr)
{

	return sendto(sock, &in_msg[0], in_msg.size(), 0,
              (struct sockaddr *)to_addr, sizeof(*to_addr));

}

std::vector<uint8_t> TGLUDPInterface::receive_msg(sockaddr_in * from_addr)
{
	std::cout << "Receiving..." << "\n";
	std::vector <uint8_t> out_vec(max_msg_size);
	socklen_t out_size;
	recvfrom(sock, &out_vec[0], max_msg_size, 0, (struct sockaddr *)from_addr, &out_size);
	std::cout << "COTGDSFS" << "\n";
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
		sockaddr_in from_addr;
		rec_msg = receive_msg(&from_addr);
		msg_queue_mutex.lock();
		if (msg_qs.find(from_addr) == msg_qs.end())
		{
			msg_qs[from_addr] = std::deque<std::vector <uint8_t> >(0);
		}
		msg_qs[from_addr].push_back(rec_msg);
		msg_queue_mutex.unlock();
	}
}

std::vector <uint8_t> TGLUDPInterface::pop_msg(sockaddr_in * in_addr)
{
	std::vector <uint8_t> out_vector;
	msg_queue_mutex.lock();
	out_vector = msg_qs[*in_addr].front();
	msg_queue_mutex.unlock();
	return out_vector;
}

int main()
{
	std::vector <uint8_t> test_msg = {1,2,3,4,5,6,7,8,9};
	int retval = 0;
	TGLUDPInterface udp_int, udp_int2;
	retval = udp_int.init("127.17.0.6", 12345);
	if (retval != 0)
	{
		std::cout << "ERROR1" << "\n";
	}
	retval = udp_int2.init("127.17.0.6", 12346);
	if (retval != 0)
	{
		std::cout << "ERROR2" << "\n";
		std::cout << errno << "\n";
	}
	udp_int.start_receive_thread();
	while(1)
	{
		sockaddr_in to_addr;
		inet_aton("127.17.0.6", &to_addr.sin_addr);
		to_addr.sin_port = 12345;
		to_addr.sin_family = AF_INET;
		retval = udp_int2.send_msg(test_msg, &to_addr);
		std::cout << "Sent: " << retval << "\n";
		sleep(3);
		to_addr.sin_port = 12346;
		std::vector <uint8_t> got = udp_int.pop_msg(&to_addr);
		for (auto g : got)
		{
			std::cout << g << "\n";
		}
	}
}
